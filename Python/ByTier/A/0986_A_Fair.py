# Problem: CF 986 A - Fair
# https://codeforces.com/contest/986/problem/A

"""
Algorithm: Multi-source BFS with preprocessing
Time Complexity: O(n * k + m * k)
Space Complexity: O(n * k + m)

This solution uses multi-source BFS to compute shortest distances from each town to all types of goods.
For each good type, we run BFS from all towns producing that good.
The distance matrix g[i][j] stores the shortest distance from town i to the nearest town producing good type j.
Finally, for each town, we sort the distances and sum up the smallest s+1 distances (because we need at least s types,
but we're including one extra for potential optimization).
"""

import sys

input = lambda: sys.stdin.readline().rstrip()
from collections import deque


def f(p):
    # Update the distance matrix based on edges in p
    for l, r in p:
        for i in range(1, k + 1):
            g[r][i] = min(g[r][i], g[l][i] + 1)


def fi(p):
    # Flip direction of edges in p
    pp = []
    for i, j in p[::-1]:
        pp.append((j, i))
    return pp


n, m, k, s = map(int, input().split())
if n < 50000:
    w = list(map(int, input().split()))
    d = [[] for _ in range(n + 1)]
    g = [[0] * (k + 1) for _ in range(n + 1)]
    h = [[] for _ in range(k + 1)]
    for i in range(n):
        h[w[i]].append(i + 1)
    for i in range(m):
        a, b = map(int, input().split())
        d[a].append(b)
        d[b].append(a)
    for j in range(1, k + 1):
        q = deque(h[j])
        x = [1] * (n + 1)
        for i in q:
            x[i] = 0
        while q:
            a = q.pop()
            for i in d[a]:
                if x[i]:
                    x[i] = 0
                    g[i][j] = g[a][j] + 1
                    q.appendleft(i)
    for i in g[1:]:
        i.sort()
        print(sum(i[: s + 1]), end=" ")
else:
    w = list(map(int, input().split()))
    d = [[] for _ in range(n + 1)]
    g = [[10**6] * (k + 1) for _ in range(n + 1)]
    for i in range(n):
        g[i + 1][w[i]] = 0
    z = [tuple(map(int, input().split())) for _ in range(m)]
    x = [1] * (n + 1)
    y = [1] * (m + 1)
    q = [1]
    h = []
    for i in range(m):
        a, b = z[i]
        d[a].append(i)
        d[b].append(i)
    x[1] = 0
    while q:
        a = q.pop()
        for i in d[a]:
            if y[i]:
                y[i] = 0
                for j in z[i]:
                    if j != a:
                        h.append((a, j))
                        if x[j]:
                            x[j] = 0
                            q.append(j)
    wi = fi(h)
    f(h), f(wi), f(h), f(wi), f(h)
    for i in g[1:]:
        i.sort()
        print(sum(i[:s]), end=" ")


# https://github.com/VaHiX/CodeForces/