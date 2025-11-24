# Problem: CF 1993 E - Xor-Grid Problem
# https://codeforces.com/contest/1993/problem/E

"""
Algorithm: Dynamic Programming on Subsets with Bitmasking
Time Complexity: O(2^n * n^2 + n * m)
Space Complexity: O(2^n * n)

This solution uses bitmask dynamic programming to find the minimum beauty
of a matrix after performing row/column operations. The key idea is that
each row/column operation changes the values in the row/column to the XOR
of all elements in that row/column. The beauty is defined as the sum of
absolute differences between adjacent cells. We compute the optimal way
to perform these operations by trying all combinations of applying
operations on rows and columns.

Approach:
1. Precompute row and column XOR values
2. Use bitmask DP to find minimum cost for choosing a subset of rows/columns
3. Calculate minimum beauty by considering both row and column operations
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def f(u, v):
    return u << 4 ^ v


t = int(input())
ans = []
a, b, c = [0] * (1 << 8), [0] * (1 << 8), [0] * (1 << 8)
pow2 = [1]
for _ in range(16):
    pow2.append(2 * pow2[-1])
inf = pow(10, 12) + 1
for _ in range(t):
    n, m = map(int, input().split())
    z = 0
    for i in range(n):
        a0 = list(map(int, input().split()))
        for j in range(m):
            a[f(i, j)] = a0[j]
            b[f(j, i)] = a0[j]
            z ^= a0[j]
    x, y = [0] * (m + 1), [0] * (n + 1)
    for i in range(n):
        for j in range(m):
            x[j] ^= a[f(i, j)]
            y[i] ^= a[f(i, j)]
    for j in range(m):
        a[f(n, j)] = x[j]
    for i in range(n):
        b[f(m, i)] = y[i]
    s = [inf] * (1 << 9)
    for w in range(2):
        for u in range(m + 1):
            a[f(n, u)] = z
            for i in range(n):
                a[f(i, u)] = y[i]
            for i in range(n + 1):
                for j in range(i + 1, n + 1):
                    d = 0
                    for k in range(m):
                        d += abs(a[f(i, k)] - a[f(j, k)])
                    c[f(i, j)] = c[f(j, i)] = d
            a[f(n, u)] = x[u]
            for i in range(n):
                a[f(i, u)] = b[f(u, i)]
            l = pow2[n + 1]
            dp = [inf] * (l << 4)
            for i in range(n + 1):
                dp[f(pow2[i], i)] = 0
            for i in range(1, l):
                d = []
                for j in range(n + 1):
                    if not i & pow2[j]:
                        d.append(j)
                for j in range(n + 1):
                    if not i & pow2[j]:
                        continue
                    dp0 = dp[f(i, j)]
                    for k in d:
                        v = f(i ^ pow2[k], k)
                        dp[v] = min(dp[v], dp0 + c[f(j, k)])
            for v in range(n + 1):
                i, mi = (l - 1) ^ pow2[v], inf
                for j in range(n + 1):
                    mi = min(mi, dp[f(i, j)])
                s[f(v, u) << 1 ^ w] = mi
        n, m = m, n
        a, b = b, a
        x, y = y, x
    ans0 = inf
    for i in range(n + 1):
        for j in range(m + 1):
            ans0 = min(ans0, s[f(i, j) << 1] + s[f(j, i) << 1 ^ 1])
    ans.append(ans0)
sys.stdout.write("\n".join(map(str, ans)))


# https://github.com/VaHiX/CodeForces/