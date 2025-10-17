# Problem: CF 2077 F - AND x OR
# https://codeforces.com/contest/2077/problem/F

"""
F. AND x OR
Algorithm: Dynamic Programming with Bitmask, Greedy Optimization
Time Complexity: O(n + m * log(m) + 2^(log(m)) * log(log(m)))
Space Complexity: O(m + 2^(log(m)))

The problem involves making two arrays 'good' by performing operations on them.
Each operation allows us to modify elements using bitwise AND and OR with a non-negative integer x.
Our goal is to find minimum moves (incrementing elements of either array) to make the pairs equal.

The solution uses:
1. Preprocessing for differences between initial arrays
2. Bitmask DP to propagate minimum distances between values in b
3. Greedy optimizations using sorted values and bitmask techniques

Key techniques:
- Prefix minimization with bitmask traversal
- Fast bit manipulation using masks
- Optimization over small bit ranges
"""

import sys

input = sys.stdin.readline
t = int(input())
for _ in range(t):
    n, m = map(int, input().split())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    out = 0
    for i in range(n):
        out += abs(a[i] - b[i])
    z = 1
    bt = 0
    while m >= z:
        z *= 2
        bt += 1
    b.sort()
    for i in range(n - 1):
        out = min(out, b[i + 1] - b[i])
    curr = [m] * z
    curr3 = [z] * z
    for v in b:
        curr[v] = 0
        curr3[v] = v
    for i in range(1, z):
        curr[i] = min(curr[i], curr[i - 1] + 1)
    curr2 = [m] * z
    for k in range(bt):
        mask = 1 << k
        for i in range(z):
            if mask & i == 0:
                j = i | mask
                curr2[j] = min(curr2[j], curr[i], curr2[i])
                curr3[j] = min(curr3[j], curr3[i])
    for v in b:
        out = min(out, curr2[v])
    st = []
    for i in range(z)[::-1]:
        if curr3[i] == z:
            continue
        assert curr3[i] <= i
        while st and curr3[st[-1]] >= i:
            st.pop()
        if st and curr3[i] == i:
            out = min(out, st[-1] - i)
        while st and curr3[st[-1]] >= curr3[i]:
            st.pop()
        st.append(i)
    """
    for v in b:
        ind = xx[v]
        if curr3[ind] < v:
            out = min(out, ind - v)"""
    print(out)


# https://github.com/VaHiX/codeForces/