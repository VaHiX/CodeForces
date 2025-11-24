# Problem: CF 1750 E - Bracket Cost
# https://codeforces.com/contest/1750/problem/E

"""
Algorithm: 
This problem involves calculating the sum of costs for all substrings of a bracket sequence.
The key insight is to understand that the "cost" of a substring is the minimum number of operations 
(insert a bracket or cyclic shift) required to make it balanced.

The algorithm uses:
1. Prefix sum to compute balance at each position
2. Sorting and prefix sum techniques to calculate contribution of each balance value
3. Monotonic stack to efficiently calculate contributions of each position

Time Complexity: O(n log n) due to sorting step
Space Complexity: O(n) for storing prefix sums and stack
"""
import sys

input = lambda: sys.stdin.readline().rstrip()
mi = lambda: map(int, input().split())
li = lambda: list(mi())


ans = []
for _ in range(int(input())):
    n = int(input())
    S = input()

    # Compute prefix sums to represent balance at each position
    f = [0] * (n + 1)
    for i in range(n):
        if S[i] == "(":
            f[i + 1] = f[i] + 1
        else:
            f[i + 1] = f[i] - 1

    res = 0

    # Sort prefix sums for calculation
    val = [f[i] for i in range(n + 1)]
    val.sort()
    for i in range(n + 1):
        res += val[i] * (n - i)

    # This part calculates contributions with careful handling of differences
    check = 0
    for i in range(n):
        res += (val[i + 1] - val[i]) * (i + 1) * (n - i)
        check += (val[i + 1] - val[i]) * (i + 1) * (n - i)

    # Using monotonic stack to compute final adjustments
    tmp_sum = 0
    st = [(-n - 1, -1)]
    for i in range(n + 1):
        # Maintain monotonicity in stack
        while st[-1][0] >= f[i]:
            m2, idx2 = st[-2]
            m1, idx1 = st[-1]
            tmp_sum -= m1 * (idx1 - idx2)
            st.pop()
        m1, idx1 = st[-1]
        tmp_sum += f[i] * (i - idx1)
        st.append((f[i], i))

        # Adjust total cost
        res -= tmp_sum - f[i]

    print(res)


# https://github.com/VaHiX/CodeForces/