# Contest 2091, Problem G: Gleb and Boating
# URL: https://codeforces.com/contest/2091/problem/G

import sys

input = lambda: sys.stdin.readline().rstrip("\r\n")
sint = lambda: int(input())
mint = lambda: map(int, input().split())
aint = lambda: list(map(int, input().split()))
###############################################
for _ in range(sint()):
    s, k = mint()
    if s % k == 0:
        print(k)
        continue
    if 2 * s > k * k:
        print(max(k - 2, 1))
        continue
    dp = [1] + [0] * s
    while k > 1:
        dp = [0] * k + dp[: s + 1 - k]
        for i in range(2 * k, s + 1):
            dp[i] |= dp[i - k]
        if dp[-1]:
            print(k)
            break
        k = max(k - 1, 1)
        dp = dp[k:] + [0] * k
        for i in range(s - k, k - 1, -1):
            dp[i - k] |= dp[i]
        k = max(k - 1, 1)
    else:
        print(1)
