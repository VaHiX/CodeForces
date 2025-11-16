# Problem: CF 1957 F1 - Frequency Mismatch (Easy Version)
# https://codeforces.com/contest/1957/problem/F1

"""
Algorithm: Tree Path Comparison using Hashing
Techniques: 
- Heavy-light decomposition with path compression
- Randomized hashing for efficient path comparison
- Bit manipulation for fast operations

Time Complexity: O(n log n + q log^2 n)
Space Complexity: O(n)

This code solves a problem where we need to compare frequency distributions of values on two paths in a tree.
For each query, we find the difference in count of each value between two paths and output the first k differing values.
"""

import io
import os
import random
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def f(u, v):
    # Hash function for combining two values
    return u << 20 ^ v


def g(u, v, w):
    # Hash function for triple (u,v,w)
    return u << 40 ^ v << 20 ^ w


def h(u, v):
    # Hash function for two values
    return u << 4 ^ v


def make_graph(n, m):
    # Build adjacency list representation of tree
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
    # BFS traversal to build parent and distance arrays
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
q1, q2 = [0] * q, [0] * q
ans0 = [0] * q
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
    q1[i], q2[i] = g(u1, v1, w1), g(u2, v2, w2)
m = max(a)
cnt = [0] * (m + 1)
for i in a[1:]:
    cnt[i] += 1
z = []
for i in range(1, m + 1):
    if cnt[i]:
        z.append(f(cnt[i].bit_length(), i))
random.shuffle(z)
p = p[1:]
s = set()
dp = [0] * (n + 1)
for _ in range(3):
    rr = [random.randint(1, 1 << 40) for _ in range(m + 1)]
    dp[1] = rr[a[1]]
    for i in p:
        dp[i] = dp[parent[i]] + rr[a[i]]
    for i in range(q):
        x1, x2 = q1[i], q2[i]
        u1, v1, w1 = x1 >> 40, (x1 >> 20) & 0xFFFFF, x1 & 0xFFFFF
        u2, v2, w2 = x2 >> 40, (x2 >> 20) & 0xFFFFF, x2 & 0xFFFFF
        c1 = dp[u1] + dp[v1] - 2 * dp[w1] + rr[a[w1]]
        c2 = dp[u2] + dp[v2] - 2 * dp[w2] + rr[a[w2]]
        if c1 ^ c2:
            s.add(i)
pow2 = [1]
for _ in range(62):
    pow2.append(2 * pow2[-1])
sp = [0]
for i in pow2:
    sp.append(sp[-1] ^ i)
w = 63
b = [0] * (m + 1)
lz = len(z)
i = 0
while s and i ^ lz:
    c, x, y = 0, [], []
    while i ^ lz:
        c0 = z[i] >> 20
        if c + c0 <= w:
            j = z[i] & 0xFFFFF
            x.append(j)
            y.append(sp[c] ^ sp[c + c0])
            b[j] = pow2[c]
            i += 1
            c += c0
        else:
            break
    m = len(x)
    dp[1] = b[a[1]]
    for j in p:
        dp[j] = dp[parent[j]] + b[a[j]]
    rm = []
    for j in s:
        x1, x2 = q1[j], q2[j]
        u1, v1, w1 = x1 >> 40, (x1 >> 20) & 0xFFFFF, x1 & 0xFFFFF
        u2, v2, w2 = x2 >> 40, (x2 >> 20) & 0xFFFFF, x2 & 0xFFFFF
        c1 = dp[u1] + dp[v1] - 2 * dp[w1] + b[a[w1]]
        c2 = dp[u2] + dp[v2] - 2 * dp[w2] + b[a[w2]]
        if c1 == c2:
            continue
        c = c1 ^ c2
        rm.append(j)
        for l, c0 in zip(x, y):
            if c & c0:
                ans0[j] = l
                break
    for j in rm:
        s.remove(j)
    for j in x:
        b[j] = 0
ans = []
for i in range(q):
    ans1 = [0] if not ans0[i] else [1, ans0[i]]
    ans.append(" ".join(map(str, ans1)))
sys.stdout.write("\n".join(ans))


# https://github.com/VaHiX/CodeForces/