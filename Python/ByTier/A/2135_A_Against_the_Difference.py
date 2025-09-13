# Contest 2135, Problem A: Against the Difference
# URL: https://codeforces.com/contest/2135/problem/A

import sys

input = lambda: sys.stdin.readline().rstrip()
ii = lambda: int(input())
mii = lambda: map(int, input().split())
lii = lambda: list(mii())


def solve():
    n = ii()
    arr = lii()
    dp = [0] * (n + 1)
    pos = [[] for _ in range(n + 1)]
    for i, x in enumerate(arr):
        dp[i + 1] = dp[i]
        p = pos[x]
        p.append(i)
        if len(p) >= x:
            dp[i + 1] = max(dp[i + 1], dp[p[-x]] + x)
    return dp[n]


for _ in range(ii()):
    print(solve())
