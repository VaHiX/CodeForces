# Contest 2025, Problem E: Card Game
# URL: https://codeforces.com/contest/2025/problem/E


MOD = 998244353
n, m = map(int, input().split())


def convolution(P, Q):
    assert len(P) == len(Q)
    R = []
    for i in range(len(P)):
        suma = 0
        for j in range(i + 1):
            suma += P[j] * Q[i - j]
            suma %= MOD
        R.append(suma)
    return R


def power(P, k):
    R = [0] * len(P)
    R[0] = 1
    while k:
        if k & 1:
            R = convolution(R, P)
        P = convolution(P, P)
        k >>= 1
    return R


dp = [1] + [0] * m
for _ in range(m):
    prev = dp
    dp = [0] * (m + 1)
    for c in range(m + 1):
        if c - 1 >= 0:
            dp[c] += prev[c - 1]
        if c + 1 <= m:
            dp[c] += prev[c + 1]
        dp[c] %= MOD
dpp = power(dp, n - 1)
ans = sum(dp[m] * dpp[m] % MOD for m in range(m + 1)) % MOD
print(ans)
