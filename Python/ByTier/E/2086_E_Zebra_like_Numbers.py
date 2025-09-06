# Contest 2086, Problem E: Zebra-like Numbers
# URL: https://codeforces.com/contest/2086/problem/E

import sys, os, io

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def f(u, v):
    return u << 7 ^ v


def g(u, k):
    if k >= m:
        return 0
    elif u <= 4:
        return 1 if k <= u else 0
    ans = 0
    while u > 4 and k >= 0:
        for i in range(1, 30):
            if u < x[i]:
                ans += dp[f(i - 1, k)]
                u, k = u - x[i - 1] - 1, k - 1
                break
            elif u == x[i]:
                ans += dp[f(i, k)]
                return ans
    if 0 <= k <= u:
        ans += 1
    return ans


t = int(input())
ans = []
m = 120
x, u = [], 1
for _ in range(30):
    x.append(u << 2)
    u = u << 2 ^ 1
dp = [0] * (1 << 12)
dp[0] = dp[1] = dp[2] = dp[3] = dp[4] = 1
for i in range(1, 30):
    for j in range(m):
        if not dp[f(i - 1, j)]:
            break
        c = dp[f(i - 1, j)]
        for k in range(4):
            dp[f(i, j + k)] += c
    dp[f(i, 4)] += 1
for _ in range(t):
    l, r, k = map(int, input().split())
    ans0 = g(r, k) - g(l - 1, k)
    ans.append(ans0)
sys.stdout.write("\n".join(map(str, ans)))
