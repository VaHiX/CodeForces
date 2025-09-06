# Contest 2052, Problem F: Fix Flooded Floor
# URL: https://codeforces.com/contest/2052/problem/F

import sys

input = lambda: sys.stdin.readline().rstrip()
ii = lambda: int(input())
mii = lambda: map(int, input().split())
lii = lambda: list(mii())

res = ["None", "Unique", "Multiple"]


def solve():
    n = ii()
    grid = [input() for _ in range(2)]
    dp = [[0, 0], [0, 0]]
    dp[1][1] = 1
    for ch1, ch2 in zip(*grid):
        ndp = [[0, 0], [0, 0]]
        if ch1 == "." and ch2 == ".":
            ndp[0][0] = dp[1][1]
            ndp[0][1] = dp[1][0]
            ndp[1][0] = dp[0][1]
            ndp[1][1] = min(dp[0][0] + dp[1][1], 2)
        elif ch1 == "." and ch2 == "#":
            ndp[0][1] = dp[1][1]
            ndp[1][1] = dp[0][1]
        elif ch1 == "#" and ch2 == ".":
            ndp[1][0] = dp[1][1]
            ndp[1][1] = dp[1][0]
        else:
            ndp[1][1] = dp[1][1]
        dp = ndp
    return res[dp[1][1]]


for _ in range(ii()):
    print(solve())
