# Contest 2127, Problem F: Hamed and AghaBalaSar
# URL: https://codeforces.com/contest/2127/problem/F

mod = 1000000007
MX = 400001

fac = [0] * MX
fac[0] = 1
for i in range(1, MX):
    fac[i] = fac[i - 1] * i % mod

inv_fac = [0] * MX
inv_fac[MX - 1] = pow(fac[MX - 1], -1, mod)
for i in range(MX - 1, 0, -1):
    inv_fac[i - 1] = inv_fac[i] * i % mod


def comb(n: int, k: int) -> int:
    return fac[n] * inv_fac[k] % mod * inv_fac[n - k] % mod


def g(n, m, l):
    if n == 0:
        return 1 if m == 0 else 0
    ans = 0
    for t in range(0, min(n, m // (l + 1)) + 1):
        res = comb(n, t) * comb(m + n - 1 - t * (l + 1), n - 1) % mod
        ans = (ans + res) % mod if t % 2 == 0 else (ans - res) % mod
    return ans


from sys import stdin

input = lambda: stdin.readline().rstrip()


def solve():
    n, m = map(int, input().split())
    ans = 0
    inv = pow(n - 1, -1, mod)
    for x in range(0, m + 1):
        g1 = g(n - 1, m - x, x)
        g2 = g(n - 2, m - 2 * x, x)
        res = (g1 * inv + g2) % mod
        ans = (ans + (n * x - m) * res) % mod
    return ans


for _ in range(int(input())):
    print(solve())
