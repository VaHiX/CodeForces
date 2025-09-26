# Contest 2071, Problem C: Trapmigiano Reggiano
# URL: https://codeforces.com/contest/2071/problem/C

import sys

input = sys.stdin.readline
for i in range(int(input())):
    n, st, en = map(int, input().split())
    g = [[] for j in range(n)]
    for j in range(n - 1):
        u, v = map(int, input().split())
        g[u - 1].append(v - 1)
        g[v - 1].append(u - 1)
    s = [en - 1]
    t = [en]
    vis = [(0 if j != en - 1 else 1) for j in range(n)]
    while s:
        parent = s.pop()
        for child in g[parent]:
            if not (vis[child]):
                s.append(child)
                t.append(child + 1)
                vis[child] = 1
    print(*t[::-1])
