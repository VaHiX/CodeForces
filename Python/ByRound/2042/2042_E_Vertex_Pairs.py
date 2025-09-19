# Contest 2042, Problem E: Vertex Pairs
# URL: https://codeforces.com/contest/2042/problem/E

import sys, os, io

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


def lca(u, v):
    while z[u] ^ z[v]:
        if dist[z[u]] >= dist[z[v]]:
            u = parent[z[u]]
        else:
            v = parent[z[v]]
    ans = u if dist[u] <= dist[v] else v
    return ans


n = int(input())
a = [0] + list(map(int, input().split()))
inf = pow(10, 9) + 1
n, n0 = 2 * n, n
G, s0 = make_graph(n, n - 1)
x = [0] * (n0 + 1)
for i in range(1, n + 1):
    x[a[i]] ^= i
r = 1
c = bytearray(n + 1)
for _ in range(2):
    p, dist, parent = bfs(r)
    cnt = [1] * (n + 1)
    for i in p[::-1][:-1]:
        cnt[parent[i]] += cnt[i]
    z = [i for i in range(n + 1)]
    for i in p:
        j, ma, di = i, -1, dist[i]
        for v in range(s0[i], s0[i + 1]):
            k = G[v]
            if dist[k] < di:
                continue
            if ma < cnt[k]:
                j, ma = k, cnt[k]
        z[j] = z[i]
    color = bytearray(n + 1)
    for i in range(1, n + 1):
        j = x[a[i]] ^ i
        if not i < j:
            continue
        k = lca(i, j)
        while not color[k] and k ^ -1:
            color[k], k = 1, parent[k]
    for i in range(n, 0, -1):
        if color[i]:
            continue
        q = [i]
        for j in q:
            color[j], k = 2, x[a[j]] ^ j
            while not color[k] and k ^ -1:
                color[k], k = 1, parent[k]
            for v in range(s0[j], s0[j + 1]):
                k = G[v]
                if not color[k] and parent[j] ^ k:
                    q.append(k)
    for i in range(n, 0, -1):
        if c[i] ^ color[i]:
            if c[i] < color[i]:
                c = color
            break
    r ^= x[a[1]]
ans = []
for i in range(1, n + 1):
    if c[i] == 1:
        ans.append(i)
k = len(ans)
print(k)
sys.stdout.write(" ".join(map(str, ans)))
