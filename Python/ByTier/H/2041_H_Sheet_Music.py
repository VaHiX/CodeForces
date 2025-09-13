# Contest 2041, Problem H: Sheet Music
# URL: https://codeforces.com/contest/2041/problem/H

mod = 998244353
nn = 10**6 + 10
fact = [1] * nn
for i in range(nn - 1):
    fact[i + 1] = fact[i] * (i + 1) % mod
invfact = [1] * nn
invfact[-1] = pow(fact[-1], mod - 2, mod)
for i in range(nn - 2, -1, -1):
    invfact[i] = invfact[i + 1] * (i + 1) % mod


def binom(n, r):
    if n < 0 or n < r or r < 0:
        return 0
    else:
        return fact[n] * invfact[r] % mod * invfact[n - r] % mod


n, k = map(int, input().split())

dp = [0] * n
rui = [0] * (n + 1)
dp[0] = 1
rui[1] = 1

for i in range(1, n):
    dp[i] = (rui[i] - rui[max(i - k + 1, 0)]) % mod
    rui[i + 1] = (dp[i] + rui[i]) % mod
# print(dp)
ans = 1
for i in range(1, n):
    ans += 2 * binom(n - 1, i) % mod * dp[i] % mod
    ans %= mod

print(ans)
