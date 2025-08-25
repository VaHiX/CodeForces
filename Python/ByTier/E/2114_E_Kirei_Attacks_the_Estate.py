# Contest 2114, Problem E: Kirei Attacks the Estate
# URL: https://codeforces.com/contest/2114/problem/E

import sys

input = lambda: sys.stdin.readline().rstrip()


for _ in range(int(input())):
    n = int(input())
    w = [0] + list(map(int, input().split())) + [0]
    d = [[] for _ in range(n + 1)]
    for _ in range(n - 1):
        a, b = map(int, input().split())
        d[a].append(b)
        d[b].append(a)
    q = [1]
    g = [-1] * (n + 2)
    x = [0] * (n + 2)
    while q:
        a = q.pop()
        b = g[a]
        c = g[b]
        x[a] = w[a] + max(0, x[c] - w[b])
        for i in d[a]:
            if i != g[a]:
                q.append(i)
                g[i] = a
    print(" ".join(map(str, x[1:-1])))
