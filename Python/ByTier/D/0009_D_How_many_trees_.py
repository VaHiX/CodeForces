# Contest 9, Problem D: How many trees?
# URL: https://codeforces.com/contest/9/problem/D

################################################################################
n, h = map(int, input().split())

# n=3
# h=3
################################################################################
dp = [[0 for i in range(n + 1)] for i in range(n + 1)]
dp[0][0] = 1

for i in range(1, n + 1):
    for l in range(i):
        r = i - l - 1
        for k in range(l + 1):
            for p in range(r + 1):
                dp[i][max(k, p) + 1] += dp[l][k] * dp[r][p]

out = 0
for i in range(h, n + 1):
    out += dp[n][i]

print(out)
