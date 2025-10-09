# Contest 1776, Problem M: Parmigiana With Seafood
# URL: https://codeforces.com/contest/1776/problem/M

import sys
from collections import deque

input = sys.stdin.buffer.readline

n = int(input())
g = [[] for _ in range(n + 1)]
for _ in range(1, n):
    u, v = map(int, input().split())
    g[u].append(v)
    g[v].append(u)

q = deque()
d = [-1] * (n + 1)
f = [0] * (n + 1)
q.append(n)
d[n] = 0
while len(q):
    u = q.popleft()
    for v in g[u]:
        if d[v] == -1:
            q.append(v)
            f[v] = u
            d[v] = d[u] + 1
if n % 2 == 0:
    print(n)
else:
    l, r = 1, n
    while l < r:
        m = (l + r + 1) // 2
        ok = True
        for i in range(m, n + 1):
            if len(g[i]) == 1 or d[i] % 2:
                ok = False
        x = [0] * (n + 1)
        x[n] = 1
        for i in range(m, n + 1):
            j = i
            while x[j] == 0:
                x[j] = 1
                j = f[j]
        for i in range(m, n + 1):
            c = 2 if i == n else 1
            for v in g[i]:
                if f[v] == i:
                    c -= x[v]
            for v in g[i]:
                if f[v] == i and c > 0:
                    x[v] = 1
                    c -= 1
        for i in range(1, n + 1):
            if x[i] and d[i] % 2 == 0:
                y = 0
                for j in g[i]:
                    y += x[j]
                if y > 2:
                    ok = False
        if ok:
            r = m - 1
        else:
            l = m
    print(l)
