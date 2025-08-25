# Contest 2109, Problem E: Binary String Wowee
# URL: https://codeforces.com/contest/2109/problem/E

from sys import stdin

input = lambda: stdin.readline().rstrip()
mod = 998244353

mx = 501
comb = [[0] * mx for _ in range(mx)]
for i in range(mx):
    comb[i][0] = 1
    for j in range(1, i + 1):
        comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % mod


def solve():
    n, k = map(int, input().split())
    s = input()
    dp = [0] * (k + 1)
    dp[0] = 1
    for i in range(n - 1, -1, -1):
        ndp = [0] * (k + 1)
        if s[i] == "0":
            for j in range(k + 1):
                m = (j + 1) // 2
                res = 0
                for p in range(j // 2, j + 1):
                    res += dp[p] * comb[m][j - p]
                    res %= mod
                ndp[j] = res
        else:
            for j in range(k + 1):
                m = j // 2
                res = 0
                for p in range((j + 1) // 2, j + 1):
                    res += dp[p] * comb[m][j - p]
                    res %= mod
                ndp[j] = res
        dp = ndp

    return dp[k]


for _ in range(int(input())):
    print(solve())
