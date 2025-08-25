# Contest 2125, Problem D: Segments Covering
# URL: https://codeforces.com/contest/2125/problem/D

import os, io

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

n, m = map(int, input().split())

mod = 998244353
nxt = [[] for i in range(m)]
az = 1


def pw(a, b):
    ret = 1
    while b:
        if b & 1:
            ret = ret * a % mod
        a = a * a % mod
        b >>= 1
    return ret


for i in range(n):
    l, r, p, q = map(int, input().split())
    l -= 1
    az *= (q - p) * pw(q, mod - 2) % mod
    az %= mod
    nxt[l].append((r, p * pw(q - p, mod - 2) % mod))

dp = [0] * (m + 1)
dp[m] = 1
for i in range(m - 1, -1, -1):
    for nx, pr in nxt[i]:
        dp[i] += pr * dp[nx] % mod
print(dp[0] * az % mod)
