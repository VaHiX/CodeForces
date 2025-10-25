# Contest 2038, Problem D: Divide OR Conquer
# URL: https://codeforces.com/contest/2038/problem/D

import sys
import math
import bisect

mod = 998244353

n, *rest = map(int, sys.stdin.read().split())
a = [0] + rest[:n]

k = n.bit_length()
st = [[0] * (n + 2) for _ in range(k + 1)]
for i in range(1, n + 1):
    st[0][i] = a[i]

for j in range(1, k + 1):
    for i in range(1, n + 1 - (1 << j) + 1):
        st[j][i] = st[j - 1][i] | st[j - 1][i + (1 << (j - 1))]


def query_or(l, r):
    length = r - l + 1
    j = length.bit_length() - 1
    return st[j][l] | st[j][r - (1 << j) + 1]


vals = [{} for _ in range(n + 2)]
vals[1][a[1]] = 0
for i in range(2, n + 1):
    vals[i][a[i]] = 0
    for x in vals[i - 1]:
        new_x = x | a[i]
        vals[i][new_x] = vals[i].get(new_x, 0) + vals[i - 1][x]

dp = [{} for _ in range(n + 2)]
dp[1][a[1]] = 1

for i in range(1, n):
    for x in dp[i]:
        cnt = dp[i][x]
        new_x = x | a[i + 1]
        dp[i + 1][new_x] = (dp[i + 1].get(new_x, 0) + cnt) % mod

        l, r = i + 1, n
        res = n + 1
        while l <= r:
            mid = (l + r) // 2
            if query_or(i + 1, mid) >= x:
                res = mid
                r = mid - 1
            else:
                l = mid + 1

        if res <= n:
            seg_x = query_or(i + 1, res)
            dp[res][seg_x] = (dp[res].get(seg_x, 0) + cnt) % mod

ans = sum(dp[n].values()) % mod
print(ans)
