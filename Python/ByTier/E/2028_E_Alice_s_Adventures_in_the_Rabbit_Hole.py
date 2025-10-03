# Contest 2028, Problem E: Alice's Adventures in the Rabbit Hole
# URL: https://codeforces.com/contest/2028/problem/E

import sys

input = sys.stdin.readline
mod = 998244353
for i in range(int(input())):
    n = int(input())
    g = [[] for j in range(n)]
    for j in range(n - 1):
        u, v = map(int, input().split())
        g[u - 1].append(v - 1)
        g[v - 1].append(u - 1)
    p = [0] * n
    vis = [(0 if j else 1) for j in range(n)]
    s, t = [0], [0]
    while s:
        parent = s.pop()
        for child in g[parent]:
            if not (vis[child]):
                vis[child] = 1
                p[child] = parent
                t.append(child)
                s.append(child)
    d = [0] * n
    for j in range(n - 1, 0, -1):
        if d[p[t[j]]] == 0 or d[p[t[j]]] > d[t[j]] + 1:
            d[p[t[j]]] = d[t[j]] + 1
    dp = [(0 if j else 1) for j in range(n)]
    vis = [(0 if j else 1) for j in range(n)]
    s = [0]
    while s:
        parent = s.pop()
        for child in g[parent]:
            if not (vis[child]):
                vis[child] = 1
                dp[child] = (dp[parent] * d[child] * pow(d[child] + 1, -1, mod)) % mod
                s.append(child)
    print(*dp)
