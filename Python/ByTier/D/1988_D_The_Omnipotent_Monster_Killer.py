# Contest 1988, Problem D: The Omnipotent Monster Killer
# URL: https://codeforces.com/contest/1988/problem/D

import sys

# from math import *
input = lambda: sys.stdin.readline().rstrip("\r\n")
sint = lambda: int(input())
mint = lambda: map(int, input().split())
aint = lambda: list(map(int, input().split()))
###############################################
T = sint()
big = float("inf")
for _ in range(T):
    n = sint()
    m = n.bit_length() + 1
    a = [0] + aint()
    g = [[] for _ in range(n + 1)]  # set up adjacency matrix
    for _ in range(n - 1):
        u, v = map(int, input().split())
        g[u].append(v)
        g[v].append(u)
    dp = [[a[i] * (b + 1) for b in range(len(g[i]) + 1)] for i in range(n + 1)]
    x = [0] * (n + 1)
    Q = [(0, 1)]
    while Q:
        f, c = Q.pop()
        if c > 0:
            Q.append((f, ~c))
            for i in g[c]:
                if i == f:
                    continue
                Q.append((c, i))
        else:
            c = ~c
            mi = -1
            mv = big
            sv = big
            for i, val in enumerate(dp[c]):
                if val <= mv:
                    sv = mv
                    mi = i
                    mv = val
                elif val < sv:
                    sv = val
            x[f] += mv + x[c]
            if mi < len(dp[f]):
                dp[f][mi] += sv - mv
    ans = min(dp[1]) + x[1]
    print(ans)
