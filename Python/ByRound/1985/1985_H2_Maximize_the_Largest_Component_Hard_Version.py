# Problem: CF 1985 H2 - Maximize the Largest Component (Hard Version)
# https://codeforces.com/contest/1985/problem/H2

"""
Algorithm: Maximize the Largest Component (Hard Version)

This problem involves finding the maximum size of a connected component of '#' characters 
after performing at most one operation of setting an entire row and column to '#'.

Approach:
1. Identify all existing connected components of '#' characters using BFS.
2. For each connected component, calculate the bounding box and use a 2D difference array 
   to mark how much each cell would contribute if that component's bounding box is covered 
   by an operation.
3. Use 2D prefix sums to get the final contribution for each cell.
4. For each cell, compute the potential maximum connected component size if we perform 
   an operation that covers that cell's row and column.

Time Complexity: O(n * m)
Space Complexity: O(n * m)

Techniques:
- BFS to find connected components
- 2D差分数组 (2D difference array) to efficiently update ranges
- 2D prefix sum to compute final contribution
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def f(u, v):
    return u * m + v


def g(u, v):
    return u * (m + 1) + v


def bfs(u):
    q, visit[u] = [u], 1
    lx, rx, ly, ry = inf, -inf, inf, -inf
    for u in q:
        i, j = divmod(u, m)
        lx, rx = min(lx, i), max(rx, i)
        ly, ry = min(ly, j), max(ry, j)
        for di, dj in d:
            ni, nj = i + di, j + dj
            if not 0 <= ni < n or not 0 <= nj < m:
                continue
            v = f(ni, nj)
            if not visit[v] and s[v]:
                visit[v] = 1
                q.append(v)
    return lx, rx, ly, ry, len(q)


t = int(input())
ans = []
d = [(1, 0), (-1, 0), (0, 1), (0, -1)]
inf = pow(10, 9) + 1
for _ in range(t):
    n, m = map(int, input().split())
    s = [0] * (n * m)
    x, y = [m] * n, [n] * m
    for i in range(n):
        s0 = list(input().rstrip())
        for j in range(m):
            if s0[j] & 1:
                s[f(i, j)] = 1
                x[i] -= 1
                y[j] -= 1
    visit = [0] * (n * m)
    cnt = [0] * ((n + 1) * (m + 1))
    for i in range(n * m):
        if visit[i] or not s[i]:
            continue
        lx, rx, ly, ry, c = bfs(i)
        lx, rx = max(lx - 1, 0), min(rx + 1, n - 1) + 1
        ly, ry = max(ly - 1, 0), min(ry + 1, m - 1) + 1
        cnt[g(lx, 0)] += c
        cnt[g(rx, 0)] -= c
        cnt[g(lx, m)] -= c
        cnt[g(rx, m)] += c
        cnt[g(0, ly)] += c
        cnt[g(0, ry)] -= c
        cnt[g(n, ly)] -= c
        cnt[g(n, ry)] += c
        cnt[g(lx, ly)] -= c
        cnt[g(lx, ry)] += c
        cnt[g(rx, ly)] += c
        cnt[g(rx, ry)] -= c
    for i in range(n + 1):
        for j in range(1, m + 1):
            cnt[g(i, j)] += cnt[g(i, j - 1)]
    l = m + 1
    for j in range(m + 1):
        for i in range(1, n + 1):
            cnt[g(i, j)] += cnt[g(i - 1, j)]
    ans0 = 0
    for i in range(n):
        for j in range(m):
            c = cnt[g(i, j)] + x[i] + y[j] - (s[f(i, j)] ^ 1)
            ans0 = max(ans0, c)
    ans.append(ans0)
sys.stdout.write("\n".join(map(str, ans)))


# https://github.com/VaHiX/CodeForces/