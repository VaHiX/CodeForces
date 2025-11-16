# Problem: CF 1796 C - Maximum Set
# https://codeforces.com/contest/1796/problem/C

"""
Algorithm/Techniques: 
- Precompute powers of 2 up to 2^30 for efficient lookup.
- For each test case, determine the maximum size of a beautiful set by finding the largest k such that there exists a pair of numbers in [l, r] where one divides the other, and the ratio is a power of 2.
- The maximum size of a beautiful set is determined by the highest power of 2 that allows at least one such pair in the interval [l, r].
- Count the number of such maximum-sized sets by iterating over possible starting points and counting valid choices, considering the divisibility constraints.

Time Complexity: O(30 * t) = O(t), where t is the number of test cases (since we precompute powers of 2 and each query is processed in constant time).
Space Complexity: O(30) = O(1), due to precomputed powers of 2.
"""

import sys

input = sys.stdin.readline
pw = []  # Precompute powers of 2
c = 1
for i in range(30):
    pw.append(c)
    c *= 2


def solve():
    l, r = map(int, input().split())  # Read input for current test case
    x, y = l, r  # Store original bounds for calculations
    cnt = 0
    # Find the largest power of 2 such that l * 2^cnt <= r
    while l * pw[cnt] <= r:
        cnt += 1
    cnt -= 1  # Adjust to get the maximum valid power of 2

    # Special case: if the maximum size is 1
    if cnt + 1 == 1:
        print(cnt + 1, y - x + 1)
        return

    # Compute how many multiples of 2^cnt exist in [l, r]
    v = r // pw[cnt]
    ans = v - x + 1  # Number of valid numbers in range which can start a beautiful set
    cur = r // ((pw[cnt] // 2) * 3)  # Compute another threshold based on 2^(cnt-1) * 3

    # Add contribution of more complex combinations if valid
    if (cur - x + 1) > 0:
        ans += (cnt) * (cur - x + 1)

    print(cnt + 1, ans % 998244353)  # Output result with modulo


for _______ in range(int(input())):  # Process each test case
    solve()


# https://github.com/VaHiX/CodeForces/