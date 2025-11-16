# Problem: CF 1983 G - Your Loss
# https://codeforces.com/contest/1983/problem/G

"""
Algorithm: Tree Path Sum with XOR
Techniques: Binary Lifting, DFS, BFS, Prefix Sums, Dynamic Programming

Time Complexity: O(n * log n + q * log n)
Space Complexity: O(n * log n)

This solution uses binary lifting to preprocess tree paths and calculate sums 
of a[p_i] XOR i for paths between nodes in a tree. The key idea is to use 
binary lifting for LCA (Lowest Common Ancestor) queries and maintain prefix sums
for efficient calculation of XOR sums along paths.

The algorithm precomputes ancestors at all 2^k distances for binary lifting,
calculates path sums using prefix sums and XOR operations, and answers queries
in logarithmic time per query.
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def make_graph(n, m):
    x, s = [0] * (2 * m), [0] * (n + 3)
    for i in range(0, 2 * m, 2):
        u, v = map(int, input().split())
        s[u + 2] += 1
        s[v + 2] += 1
        x[i], x[i + 1] = u, v
    for i in range(3, n + 3):
        s[i] += s[i - 1]
    G = [0] * (2 * m)
    for i in range(2 * m):
        j = x[i] + 1
        G[s[j]] = x[i ^ 1]
        s[j] += 1
    return G, s


def bfs(s):
    q = [s]
    dist = [inf] * (n + 1)
    dist[s] = 0
    parent = [0] * (n + 1)
    for i in q:
        di = dist[i]
        for v in range(s0[i], s0[i + 1]):
            j = G[v]
            if dist[j] == inf:
                q.append(j)
                dist[j] = di + 1
                parent[j] = i
    return q, dist, parent


def f(u, v):
    return u << 19 ^ v


def g(u, v):
    return u * q + v


t = int(input())
ans = []
pow2 = [1]
for _ in range(18):
    pow2.append(2 * pow2[-1])
inf = pow(10, 9) + 1
dp1 = [0] * (18 << 19)
dp2 = [0] * (1 << 19)
dp3 = [0] * (1 << 19)
q0 = [0] * (1 << 19)
q1 = [0] * (1 << 21)
cnt = [0] * (1 << 19)
for _ in range(t):
    n = int(input())
    G, s0 = make_graph(n, n - 1)
    a = [0] + list(map(int, input().split()))
    q, dist = [], [0] * (n + 1)
    for i in range(1, n + 1):
        cnt[i] = s0[i + 1] - s0[i]
        if cnt[i] <= 1:
            q.append(i)
    for i in q:
        di = dist[i]
        for v in range(s0[i], s0[i + 1]):
            j = G[v]
            if cnt[j] <= 1:
                continue
            dist[j] = max(dist[j], di + 1)
            cnt[j] -= 1
            if cnt[j] == 1:
                q.append(j)
    s = q[-1]
    p0, dist, parent = bfs(s)
    dist[0] = -1
    for i in range(1, n + 1):
        dp1[i] = parent[i]
    for i in range(1, 18):
        for j in range(1, n + 1):
            dp1[f(i, j)] = dp1[f(i - 1, dp1[f(i - 1, j)])]
    q = int(input())
    ans0 = [0] * q
    for i in range(q):
        x, y = map(int, input().split())
        u, v = x, y
        if dist[u] < dist[v]:
            u, v = v, u
        d = dist[u] - dist[v]
        while d:
            j = d.bit_length() - 1
            u, d = dp1[f(j, u)], d ^ pow2[j]
        for j in range(17, -1, -1):
            if dp1[f(j, u)] ^ dp1[f(j, v)]:
                u, v = dp1[f(j, u)], dp1[f(j, v)]
        z = u if u == v else parent[u]
        q0[i << 2 ^ 0], q0[i << 2 ^ 1], q0[i << 2 ^ 2], q0[i << 2 ^ 3] = x, y, z, x
        s, v, d, q1[i] = dist[x] + dist[y] - 2 * dist[z] + 1, y, dist[z], y
        for j in range(18):
            if s & pow2[j]:
                v, s = dp1[f(j, v)], s ^ pow2[j]
            q1[g(j + 1, i)] = v if dist[v] >= d else parent[z]
        ans0[i] -= (dist[x] - dist[z]) ^ a[z]
    b = (1 << 19) - 1
    for i in range(18, -1, -1):
        pi = pow2[i]
        b ^= pi
        for j in p0:
            dp2[j] = dp2[parent[j]] + (a[j] & pi)
        if i + 1 < 18:
            for j in p0[::-1]:
                k, l = dp1[f(i, j)], dp1[f(i + 1, j)]
                dp3[j] = dp2[j] + dp2[l] + pi * pi - 2 * dp2[k]
            for j in p0:
                dp3[j] += dp3[dp1[f(i + 1, j)]]
        for j in range(q):
            x, y, z = q0[j << 2 ^ 0], q0[j << 2 ^ 1], q0[j << 2 ^ 2]
            dx, dy, ans1 = dist[x] - dist[z] + 1, dist[y] - dist[z] + 1, 0
            s = dx + dy - 1
            d = min(s & b, dy)
            if d and not (s - 1) & pi:
                ans1 += dp2[y]
                s, dy, y = s - d, dy - d, q1[g(i, j)]
                ans1 -= dp2[y]
            elif d and (s - 1) & pi:
                ans1 += d * pi - dp2[y]
                s, dy, y = s - d, dy - d, q1[g(i, j)]
                ans1 += dp2[y]
            d = min(pi, dy)
            if (s - 1) & pi:
                ans1 += d * pi - dp2[y]
                dy -= d
                y = parent[z] if d < pi else dp1[f(i, y)]
                ans1 += dp2[y]
            w = q0[j << 2 ^ 3]
            if dist[w] - dist[z] + 1 >= pi << 1 and i + 1 < 18:
                q0[j << 2 ^ 3] = dp1[f(i + 1, w)]
            v = q0[j << 2 ^ 3]
            if dx:
                ans1 += dp3[x] - dp3[v]
                d = dist[v] - dist[z] + 1
                if d:
                    w = parent[z] if d <= pi else dp1[f(i, v)]
                    ans1 += dp2[v] - dp2[w]
                    v = parent[z]
                    ans1 += (pi * (dist[w] - dist[v])) - (dp2[w] - dp2[v])
            if dy:
                d, v = dy >> (i + 1) << (i + 1), y
                while d:
                    k = d.bit_length() - 1
                    v, d = dp1[f(k, v)], d ^ pow2[k]
                ans1 += dp3[y] - dp3[v]
                d = dist[v] - dist[z] + 1
                if d:
                    w = parent[z] if d <= pi else dp1[f(i, v)]
                    ans1 += dp2[v] - dp2[w]
                    v = parent[z]
                    ans1 += (pi * (dist[w] - dist[v])) - (dp2[w] - dp2[v])
            ans0[j] += ans1
    ans.append("\n".join(map(str, ans0)))
sys.stdout.write("\n".join(ans))


# https://github.com/VaHiX/CodeForces/