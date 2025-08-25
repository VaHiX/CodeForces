# Contest 2049, Problem D: Shift + Esc
# URL: https://codeforces.com/contest/2049/problem/D

from sys import stdin

inp = stdin.readline
Inf = 10**16

t = int(inp())

for _ in range(t):
    n, m, k = map(int, inp().split())
    dp = [[Inf] * m for _ in range(n + 1)]
    dp[0][0] = 0

    for i in range(1, n + 1):
        arr = [int(x) for x in inp().split()]
        dpr = [Inf for _ in range(m)]

        for j in range(m):
            for r in range(m):
                dpr[r] = min(dpr[r], dp[i - 1][j] + k * r) + arr[(j + r) % m]
            dp[i][j] = min(dpr)

    print(dp[n][m - 1])
