# Contest 2045, Problem G: X Aura
# URL: https://codeforces.com/contest/2045/problem/G

import sys, math

input = sys.stdin.readline

rn = lambda: int(input())
rs = lambda: input().strip()
rl = lambda: list(map(int, input().split()))
# sys.setrecursionlimit(500000)

ts = lambda: [[0] * (c + 1) for _ in range(r + 1)]

r, c, x = rl()
h = [rs() for _ in range(r)]


def calc_dp(h):
    dp1, dp2 = ts(), ts()
    for i in range(r):
        for j in range(c):
            dp1[i][j], dp2[i][j] = -(1 << 60), 1 << 60
            if i > 0:
                dp1[i][j] = max(
                    dp1[i][j], dp1[i - 1][j] - (ord(h[i][j]) - ord(h[i - 1][j])) ** x
                )
                dp2[i][j] = min(
                    dp2[i][j], dp2[i - 1][j] - (ord(h[i][j]) - ord(h[i - 1][j])) ** x
                )
            if j > 0:
                dp1[i][j] = max(
                    dp1[i][j], dp1[i][j - 1] - (ord(h[i][j]) - ord(h[i][j - 1])) ** x
                )
                dp2[i][j] = min(
                    dp2[i][j], dp2[i][j - 1] - (ord(h[i][j]) - ord(h[i][j - 1])) ** x
                )
            if i == 0 and j == 0:
                dp1[i][j], dp2[i][j] = 0, 0
            if dp1[i][j] != dp2[i][j]:
                return False, dp1
    return True, dp1


rd, dp = calc_dp(h)
# lf, _ = calc_dp([row[::-1] for row in h])


def solve():
    a, b, c, d = rl()
    print(dp[c - 1][d - 1] - dp[a - 1][b - 1] if rd else "INVALID")


[solve() for _ in range(rn())]
