# Contest 1107, Problem F: Vasya and Endless Credits
# URL: https://codeforces.com/contest/1107/problem/F

import sys, os, io

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def f(u, v):
    return u << 10 ^ v


n = int(input())
a0, b0, k0 = [0] * n, [0] * n, [0] * n
for i in range(n):
    a, b, k = map(int, input().split())
    a0[i], b0[i], k0[i] = a, b, k
u = [f(b0[i], i) for i in range(n)]
u = [i & 0x3FF for i in sorted(u, reverse=True)]
dp = [0] * (n + 1)
for i in range(1, n + 1):
    j = u[i - 1]
    a, b, k = a0[j], b0[j], k0[j]
    dp0 = [0] * (n + 1)
    x = max(a - b * k, 0)
    for j in range(i, -1, -1):
        dp0[j] = max(dp[j] + x, dp[j - 1] + a - b * (j - 1)) if j else dp[j] + x
    dp = dp0
ans = max(dp)
print(ans)
