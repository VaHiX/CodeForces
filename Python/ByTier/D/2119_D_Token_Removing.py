# Contest 2119, Problem D: Token Removing
# URL: https://codeforces.com/contest/2119/problem/D

for T in range(int(input())):
    N, M = map(int, input().split())
    dp = [1] + [0] * N
    for v in range(1, N + 1):
        for r in range(v, 0, -1):
            dp[r] += dp[r - 1] * (N + 1 - v) * (v - (r - 1)) % M
    print(sum(dp) % M)
