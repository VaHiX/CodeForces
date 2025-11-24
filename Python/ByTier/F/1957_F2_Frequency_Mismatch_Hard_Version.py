# Problem: CF 1957 F2 - Frequency Mismatch (Hard Version)
# https://codeforces.com/contest/1957/problem/F2

"""
Algorithm: Tree Path Query with Frequency Comparison
Technique: HLD (Heavy-Light Decomposition) + Bit manipulation + Hashing

Time Complexity: O(n log n + q * sqrt(m) * log m) where m is the maximum value
Space Complexity: O(n + m + q)

This solution uses Heavy-Light Decomposition to efficiently process path queries.
For each query, we compute the frequency of each value on both paths and compare them.
The comparison is done using XOR and bit manipulation for efficient lookup.
"""

import io
import os
import random
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def f(u, v):
    # Bit manipulation function for hashing
    return u << 20 ^ v


def g(u, v, w):
    # Bit manipulation function for storing path information
    return u << 40 ^ v << 20 ^ w


def h(u, v):
    # Bit manipulation function for indexing
    return u << 4 ^ v


def make_graph(n, m):
    # Build adjacency list representation of the tree
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
    # BFS to find distances and parents for HLD
    q = [s]
    dist = [inf] * (n + 1)
    dist[s] = 0
    parent = [-1] * (n + 1)
    for i in q:
        di = dist[i]
        for v in range(s0[i], s0[i + 1]):
            j = G[v]
            if dist[j] == inf:
                q.append(j)
                dist[j] = di + 1
                parent[j] = i
    return q, dist, parent


n = int(input())
a = [0] + list(map(int, input().split()))
G, s0 = make_graph(n, n - 1)
inf = pow(10, 9) + 1
p, dist, parent = bfs(1)
cnt = [1] * (n + 1)
for i in p[::-1][:-1]:
    cnt[parent[i]] += cnt[i]
x = [i for i in range(n + 1)]
for i in p:
    j, ma, di = i, -1, dist[i]
    for v in range(s0[i], s0[i + 1]):
        k = G[v]
        if dist[k] < di:
            continue
        if ma < cnt[k]:
            j, ma = k, cnt[k]
    x[j] = x[i]
q = int(input())
q1, q2, k0 = [0] * q, [0] * q, [0] * q
ans0 = [0] * (q << 4)
for i in range(q):
    u1, v1, u2, v2, k = map(int, input().split())
    u, v = u1, v1
    while x[u] ^ x[v]:
        if dist[x[u]] >= dist[x[v]]:
            u = parent[x[u]]
        else:
            v = parent[x[v]]
    w1 = u if dist[u] <= dist[v] else v
    u, v = u2, v2
    while x[u] ^ x[v]:
        if dist[x[u]] >= dist[x[v]]:
            u = parent[x[u]]
        else:
            v = parent[x[v]]
    w2 = u if dist[u] <= dist[v] else v
    q1[i], q2[i], k0[i] = g(u1, v1, w1), g(u2, v2, w2), k
m = max(a)
cnt = [0] * (m + 1)
for i in a[1:]:
    cnt[i] += 1
y, z = [], []
for i in range(1, m + 1):
    if cnt[i]:
        z.append(f(cnt[i].bit_length(), i))
random.shuffle(z)
pow2 = [1]
w = 6000
for _ in range(w):
    pow2.append(2 * pow2[-1])
pow2.append(0)
sp = [0]
for i in pow2:
    sp.append(sp[-1] ^ i)
b = [-1] * (m + 1)
p = p[1:]
dp = [0] * (n + 1)
lz = len(z)
i = 0
x, y = [0] * w, [0] * w
while i ^ lz:
    c = 0
    while i ^ lz:
        c0 = z[i] >> 20
        if c + c0 <= w:
            j = z[i] & 0xFFFFF
            for k in range(c, c + c0):
                x[k], y[k] = j, c
            b[j] = c
            i += 1
            c += c0
        else:
            break
    dp[1] = pow2[b[a[1]]]
    for j in p:
        dp[j] = dp[parent[j]] + pow2[b[a[j]]]
    for j in range(q):
        if not k0[j]:
            continue
        x1, x2, k = q1[j], q2[j], k0[j]
        u1, v1, w1 = x1 >> 40, (x1 >> 20) & 0xFFFFF, x1 & 0xFFFFF
        u2, v2, w2 = x2 >> 40, (x2 >> 20) & 0xFFFFF, x2 & 0xFFFFF
        c1 = dp[u1] + dp[v1] - 2 * dp[w1] + pow2[b[a[w1]]]
        c2 = dp[u2] + dp[v2] - 2 * dp[w2] + pow2[b[a[w2]]]
        if c1 == c2:
            continue
        c = c1 ^ c2
        while c and k:
            l = c.bit_length() - 1
            ans0[h(j, k)] = x[l]
            c &= sp[y[l]]
            k -= 1
        k0[j] = k
    for j in x:
        b[j] = -1
ans = []
for i in range(q):
    ans1 = [0]
    for j in range(16):
        if ans0[h(i, j)]:
            ans1.append(ans0[h(i, j)])
    ans1[0] = len(ans1) - 1
    ans.append(" ".join(map(str, ans1)))
sys.stdout.write("\n".join(ans))


# https://github.com/VaHiX/CodeForces/