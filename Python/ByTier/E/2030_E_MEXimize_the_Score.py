# Contest 2030, Problem E: MEXimize the Score
# URL: https://codeforces.com/contest/2030/problem/E

import sys

MOD = 998244353
MX = 2 * (10**5) + 1

p2 = [1] * (MX + 1)
for i in range(1, MX + 1):
    p2[i] = p2[i - 1] * 2 % MOD

fac = [0] * MX
fac[0] = 1
for i in range(1, MX):
    fac[i] = fac[i - 1] * i % MOD

inv_fac = [0] * MX
inv_fac[MX - 1] = pow(fac[MX - 1], -1, MOD)
for i in range(MX - 1, 0, -1):
    inv_fac[i - 1] = inv_fac[i] * i % MOD


def C(n, k):
    return fac[n] * inv_fac[k] % MOD * inv_fac[n - k] % MOD


def solve():
    line = sys.stdin.readline().split()
    n = int(line[0])
    line = sys.stdin.readline().split()
    cnt = [0] * n
    for x in line:
        cnt[int(x)] += 1

    dp = [0] * (n + 1)
    dpn = [0] * (n + 1)
    ans, res, mi = 0, n, n
    dp[n] = 1
    for x in range(n):
        if cnt[x] == 0:
            break
        res -= cnt[x]
        s = sum(dp[1 : mi + 1]) % MOD
        mi = min(mi, cnt[x])
        sn = p2[cnt[x]] - 1
        for i in range(1, mi + 1):
            dpn[i] = (dp[i] * sn + s * C(cnt[x], i) - dp[i] * C(cnt[x], i)) % MOD
            ans = (ans + i * dpn[i] * p2[res]) % MOD
            s = (s - dp[i]) % MOD
            sn = (sn - C(cnt[x], i)) % MOD
        dp, dpn = dpn, dp
        # print(ans, res, mi, dp[1:mi + 1])

    sys.stdout.write(str(ans) + "\n")


line = sys.stdin.readline().split()
T = int(line[0])
for t in range(T):
    solve()
