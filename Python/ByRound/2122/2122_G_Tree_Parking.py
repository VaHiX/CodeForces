# Contest 2122, Problem G: Tree Parking
# URL: https://codeforces.com/contest/2122/problem/G

from sys import stdin

input = lambda: stdin.readline()[:-1]

mod = 998244353
table_size = 5 * 10**5

fac = [1] * (table_size + 1)
finv = [1] * (table_size + 1)

for i in range(2, table_size + 1):
    fac[i] = fac[i - 1] * i % mod
finv[table_size] = pow(fac[table_size], mod - 2, mod)
for i in range(table_size - 1, -1, -1):
    finv[i] = finv[i + 1] * (i + 1) % mod


def rebuild(n):
    global table_size, fac, finv
    fac += [0] * (n - table_size)
    fac += [0] * (n - table_size)
    finv += [0] * (n - table_size)
    for i in range(table_size + 1, n + 1):
        fac[i] = fac[i - 1] * i % mod
    finv[n] = inv(fac[n])
    for i in range(n - 1, table_size, -1):
        finv[i] = finv[i + 1] * (i + 1) % mod
    table_size = n


def binom(n, k):
    if n < 0 or k < 0:
        return 0
    if k > n:
        return 0
    if n > table_size:
        rebuild(n + 10**4)
    return (fac[n] * finv[k] % mod) * finv[n - k] % mod


def fpow(x, k):
    res = 1
    while k:
        if k & 1:
            res = res * x % mod
        x = x * x % mod
        k >>= 1
    return res


def inv(a):
    if a < table_size:
        return fac[a - 1] * finv[a] % mod
    return fpow(a, mod - 2)


def T(n, k):
    res = 0
    sgn = 1
    for j in range(k + 1):
        res += sgn * fpow(k - j, n) * binom(n + 1, j)
        sgn = -sgn
        res %= mod
    return res


def solve():
    N, K = map(int, input().split())
    ans = fac[2 * N - 1] * inv(fpow(2, N - 1)) % mod * T(N - 1, K) % mod
    print(ans)
    return 0


for _ in range(int(input())):
    solve()
