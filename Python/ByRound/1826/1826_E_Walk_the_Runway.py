# Problem: CF 1826 E - Walk the Runway
# https://codeforces.com/contest/1826/problem/E

"""
Algorithm: Dynamic Programming with Bitset Optimization
Time Complexity: O(m * n^2 / 64 + n^2)
Space Complexity: O(n^2 / 64 + n)

This solution uses bitset optimization to efficiently track valid model sequences
across different cities. For each city, we precompute which models can follow
another model (strictly increasing rating requirement). Then, we use dynamic
programming to find the maximum profit achievable by selecting models in valid orders.
"""

import io
import os

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def make_graph(n, m):
    # Build adjacency list representation for the graph
    x, s = [0] * (2 * m), [0] * (n + 3)
    for i in range(0, 2 * m, 2):
        u, v = r[i >> 1], i >> 1
        s[u + 2] += 1
        x[i], x[i + 1] = u, v
    for i in range(3, n + 3):
        s[i] += s[i - 1]
    G = [0] * m
    for i in range(0, 2 * m, 2):
        j = x[i] + 1
        G[s[j]] = x[i ^ 1]
        s[j] += 1
    return G, s


m, n = map(int, input().split())
p = list(map(int, input().split()))
u = 63
pow2 = [1]
for _ in range(u - 1):
    pow2.append(2 * pow2[-1])
z = sum(pow2)
l = n // u + min(n % u, 1)
x = [z] * (l * n)
for _ in range(m):
    r = list(map(int, input().split()))
    y, s = make_graph(n, n)
    b = [z] * l
    for i in range(1, n + 1):
        for j in range(s[i], s[i + 1]):
            b[y[j] // u] ^= pow2[y[j] % u]
        for v in range(s[i], s[i + 1]):
            j = y[v] * l
            for k in range(l):
                x[j + k] &= b[k]
dp = [0] * n
for i in y:
    dp0 = dp[i] + p[i]
    j = i * l
    for k in range(n):
        if x[j + k // u] & pow2[k % u]:
            dp[k] = max(dp[k], dp0)
    dp[i] += p[i]
ans = max(dp)
print(ans)


# https://github.com/VaHiX/CodeForces/