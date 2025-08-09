# Contest 2130, Problem F: Permutation Blackhole
# URL: https://codeforces.com/contest/2130/problem/F

import sys

data = sys.stdin.read().split()
if not data:
    exit(0)
it = iter(data)
MOD = 998244353
N = 100
K = 13
ch = [[0] * (N + 1) for _ in range(N + 1)]
ch[0][0] = 1
for i in range(1, N):
    ch[i][0] = 1
    pi = ch[i-1]
    ci = ch[i]
    for j in range(1, i+1):
        ci[j] = (pi[j] + pi[j-1]) % MOD
t = int(next(it))
out_lines = []
is_zero_or_K = [False] * (K+1)
for i in range(K+1):
    if i == 0 or i == K:
        is_zero_or_K[i] = True
for _ in range(t):
    n = int(next(it))
    kk = [0]*n
    ok = True
    all_unknown = True
    for i in range(n):
        x = int(next(it))
        if x >= K:
            ok = False
        if x == -1:
            kk[i] = K
        else:
            kk[i] = x
            all_unknown = False
    if not ok:
        out_lines.append("0")
        continue
    if all_unknown:
        fac = 1
        for i in range(1, n+1):
            fac = fac * i % MOD
        out_lines.append(str(fac))
        continue
    dp = [[[[0]*(K+1) for _ in range(K+1)] for _ in range(n)] for _ in range(n)]
    for length in range(0, n):
        for l in range(0, n - length):
            r = l + length
            row_dp_lr = dp[l][r]
            for kl in range(0, K+1):
                for kr in range(0, K+1):
                    x_val = 0
                    for m in range(l, r+1):
                        kl_ = kl
                        kr_ = kr
                        if l != 0 and (r+1 == n or m - l <= r - m):
                            if kl_ < K:
                                kl_ -= 1
                        elif r+1 < n:
                            if kr_ < K:
                                kr_ -= 1
                        if kl_ < 0 or kr_ < 0:
                            continue
                        km = kk[m]
                        comb_coeff = ch[r - l][m - l]
                        if km < K:
                            for kml in range(0, km+1):
                                kmr = km - kml
                                if l < m:
                                    xl = dp[l][m-1][kl_][kml]
                                    if xl == 0:
                                        continue
                                else:
                                    if not (is_zero_or_K[kl_] and kml == 0):
                                        continue
                                    xl = 1
                                if m < r:
                                    xr = dp[m+1][r][kmr][kr_]
                                    if xr == 0:
                                        continue
                                else:
                                    if not (kmr == 0 and is_zero_or_K[kr_]):
                                        continue
                                    xr = 1
                                x_val = (x_val + xl * xr % MOD * comb_coeff) % MOD
                        else:
                            if l < m:
                                xl = dp[l][m-1][kl_][K]
                                if xl == 0:
                                    continue
                            else:
                                if not is_zero_or_K[kl_]:
                                    continue
                                xl = 1
                            if m < r:
                                xr = dp[m+1][r][K][kr_]
                                if xr == 0:
                                    continue
                            else:
                                if not is_zero_or_K[kr_]:
                                    continue
                                xr = 1
                            x_val = (x_val + xl * xr % MOD * comb_coeff) % MOD
                    row_dp_lr[kl][kr] = x_val
    ans = dp[0][n-1][0][0]
    out_lines.append(str(ans))
sys.stdout.write("\n".join(out_lines))
