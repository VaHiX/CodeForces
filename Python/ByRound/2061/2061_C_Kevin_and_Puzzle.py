# Contest 2061, Problem C: Kevin and Puzzle
# URL: https://codeforces.com/contest/2061/problem/C

import sys

input = sys.stdin.readline
MOD = 998244353

for _ in range(int(input())):
    n = int(input())
    a = [0] + list(map(int, input().split()))
    dp = [0] * (n + 1)
    dp[0] = 1

    for i in range(1, n + 1):
        if a[i] == a[i - 1]:
            dp[i] += dp[i - 1] % MOD
        if (i > 1) and (a[i] - 1 == a[i - 2]):
            dp[i] += dp[i - 2] % MOD

    print((dp[n] + dp[n - 1]) % MOD)
