# Contest 2075, Problem D: Equalization
# URL: https://codeforces.com/contest/2075/problem/D

import sys, os, io

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def f(u, v):
    return u << 7 ^ v


t = int(input())
ans = []
inf = 1 << 62
l = 30
dp = [inf] * (1 << 14)
dp[0] = 0
for i in range(1, l):
    p = 1 << i
    for j in range(3 * l, -1, -1):
        for k in range(3 * l, -1, -1):
            mi = inf
            if i <= j:
                mi = min(mi, dp[f(j - i, k)] ^ p)
            if i <= k:
                mi = min(mi, dp[f(j, k - i)] ^ p)
            dp[f(j, k)] = min(mi, dp[f(j, k)])
mi = list(dp)
for i in range(3 * l, -1, -1):
    for j in range(3 * l, -1, -1):
        mi[f(i, j)] = min(mi[f(i, j)], mi[f(i + 1, j)], mi[f(i, j + 1)])
for _ in range(t):
    x, y = map(int, input().split())
    n, m = x.bit_length(), y.bit_length()
    ans0 = mi[f(n, m)]
    while min(n, m) and x >> (n - 1) == y >> (m - 1):
        n, m = n - 1, m - 1
        ans0 = min(ans0, dp[f(n, m)])
    ans.append(ans0)
sys.stdout.write("\n".join(map(str, ans)))
