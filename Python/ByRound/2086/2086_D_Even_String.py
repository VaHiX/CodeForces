# Contest 2086, Problem D: Even String
# URL: https://codeforces.com/contest/2086/problem/D

# edu 177 D
import sys

input = lambda: sys.stdin.readline().rstrip("\r\n")
sint = lambda: int(input())
mint = lambda: map(int, input().split())
aint = lambda: list(map(int, input().split()))
###############################################
mod = 998244353
nm = 10**6
fact = [1] * (nm + 1)
for i in range(2, nm + 1):
    fact[i] = fact[i - 1] * i % mod
T = sint()
for _ in range(T):
    a = aint()
    tot = sum(a)
    even = tot // 2
    dp = [1] + [0] * even
    tmp = 1
    for i in a:
        if i == 0:
            continue
        for j in range(even, i - 1, -1):
            dp[j] = (dp[j] + dp[j - i]) % mod
        tmp = (tmp * fact[i]) % mod
    ans = fact[tot - even] * fact[even] * pow(tmp, -1, mod) * dp[-1]
    ans %= mod
    print(ans)
