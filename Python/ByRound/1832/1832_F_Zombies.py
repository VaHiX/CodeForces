# Problem: CF 1832 F - Zombies
# https://codeforces.com/contest/1832/problem/F

"""
Code Purpose:
This program solves a complex optimization problem involving zombie defense in a post-apocalyptic base.
It uses dynamic programming with segment trees and sparse tables to assign k generators to n entrances,
ensuring maximum zombie entry count after optimal placement of generators.

Key Algorithms:
- Segment trees for range queries
- Sparse table approach with binary search for efficient DP transitions
- Bit manipulation for compact storage and indexing

Time Complexity:
O(n^2 * log(n)) where n is the number of entrances.
The DP transition with segment tree optimization requires O(n^2 * log(n)) time.

Space Complexity:
O(n^2) for the DP arrays and auxiliary structures.

"""

import io
import os

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def f(u, v):
    # Bit manipulation to combine two values into one
    return u << 20 ^ v


def g(u, v):
    # Indexing helper for 2D array using linearization
    return u * ls + v


def h(u, v):
    # Indexing helper for 2D DP using linearization
    return u * (n + 1) + v


n, k, x, m = map(int, input().split())
l, r, z = [0] * n, [0] * n, [0] * n
s = set()
for i in range(n):
    l0, r0 = map(int, input().split())
    l[i], r[i], z[i] = l0, r0, f(l0 + r0, i)  # Combine l and r values with index
    s.add(l0)  # Add start points
    s.add(r0 - m)  # Add end points to check generator placement
s = list(s)
s.sort()
z.sort()
ls = len(s)
cnt = [0] * ((n + 1) * ls)
for i in range(n):
    # Get original l and r from the sorted z array
    l0, r0 = l[z[i] & 0xFFFFF], r[z[i] & 0xFFFFF]
    for j in range(ls):
        l1, r1 = s[j], s[j] + m  # Generator placement interval
        # Compute total zombies entering from this entrance for this generator placement
        cnt[g(i + 1, j)] = cnt[g(i, j)] + max(min(r0, r1) - max(l0, l1), 0)
s = sum(r) - sum(l)  # Total manual defense time over all entrances
n2 = (n + 1) * (n + 1)
inf = pow(10, 15) + 1
c = [-inf] * n2
dp = [0] * n2
u = 0
for i in range(n):
    ma, v = -inf, 0
    for j in range(u, ls):
        # Difference in coverage for placing generator at position j versus previous
        c0 = cnt[g(i + 1, j)] - cnt[g(i, j)]
        if ma < c0:
            ma, v = c0, j
    dp[h(i, i + 1)], c[h(i, i + 1)] = v, ma  # Store placement and value
    u = v  # Update upper bound for next iteration
for i in range(2, n + 1):
    for l_idx in range(n - i + 1):
        r_idx = l_idx + i
        ma, v = -inf, 0
        # Try different generator placements to optimize for this subinterval
        for j in range(dp[h(l_idx, r_idx - 1)], dp[h(l_idx + 1, r_idx)] + 1):
            c0 = cnt[g(r_idx, j)] - cnt[g(l_idx, j)]
            if ma < c0:
                ma, v = c0, j
        dp[h(l_idx, r_idx)], c[h(l_idx, r_idx)] = v, ma

for i in range(n + 1):
    c[h(i, i)] = 0  # No cost for self
dp = [-inf] * (n + 1)
dp[0] = 0  # Base case: Zero cost for no entrances
for i in range(k):
    dp0 = [-inf] * (n + 1)
    st = [h(i, n) * n2 + h(i + 1, n)]  # Initial stack for BFS-like computation
    while st:
        u, v = divmod(st.pop(), n2)  # Decompose stack elements
        l0, r0 = divmod(u, n + 1)  # Get left and right boundaries
        l1, r1 = divmod(v, n + 1)  # Get left and right boundaries of subinterval
        m1 = (l1 + r1) >> 1  # Mid point for binary search optimization
        ma, m0 = -inf, -1
        # Find the best split point using greedy selection
        for j in range(l0, r0 + 1):
            c0 = dp[j] + c[h(j, m1)]
            if ma < c0:
                ma, m0 = c0, j
        dp0[m1] = ma
        # Push left subtree if necessary
        if l1 ^ m1:
            st.append(h(l0, m0) * n2 + h(l1, m1 - 1))
        # Push right subtree if necessary
        if m1 ^ r1:
            st.append(h(m0, r0) * n2 + h(m1 + 1, r1))
    dp = dp0  # Update dp array for next iteration
ans = (x - m) * n - s + dp[n]  # Total zombies that enter
print(ans)


# https://github.com/VaHiX/CodeForces/