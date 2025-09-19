# Contest 2060, Problem F: Multiplicative Arrays
# URL: https://codeforces.com/contest/2060/problem/F

from functools import lru_cache

mod = 998244353
kmax = 100000
rmax = 16

ways = [[0] * (kmax + 1) for _ in range(rmax + 1)]


@lru_cache(None)
def mod_inv(a, p=mod):
    res, base = 1, a % p
    exp = p - 2
    while exp > 0:
        if exp & 1:
            res = (res * base) % p
        base = (base * base) % p
        exp >>= 1
    return res


def comb(n, r):
    if r > n:
        return 0
    ans = 1 % mod
    nmod = n % mod
    for i in range(r):
        term = ((nmod - i) % mod + mod) % mod
        ans = (ans * term) % mod
        ans = (ans * invs[i + 1]) % mod
    return ans


invs = [0] * 18
for i in range(1, 18):
    invs[i] = mod_inv(i)

for x in range(2, kmax + 1):
    ways[1][x] = 1

for r in range(2, rmax + 1):
    for x in range(1, kmax + 1):
        w = ways[r - 1][x]
        if w != 0:
            for muls in range(2 * x, kmax + 1, x):
                ways[r][muls] = (ways[r][muls] + w) % mod

for _ in range(int(input())):
    k, n = map(int, input().split())

    binval = [0] * (rmax + 1)
    for r in range(1, rmax + 1):
        if r <= n:
            binval[r] = comb(n + 1, r + 1)
        else:
            binval[r] = 0

    ans = [0] * (k + 1)
    ans[1] = n % mod

    for x in range(2, k + 1):
        sumx = 0
        for r in range(1, rmax + 1):
            if binval[r] == 0:
                break
            w = ways[r][x]
            if w != 0:
                tmp = (w * binval[r]) % mod
                sumx = (sumx + tmp) % mod
        ans[x] = sumx

    print(" ".join(map(str, ans[1:])))
