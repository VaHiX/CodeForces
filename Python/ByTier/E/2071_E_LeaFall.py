# Contest 2071, Problem E: LeaFall
# URL: https://codeforces.com/contest/2071/problem/E

from sys import stdin

input = lambda: stdin.readline().rstrip()
mod = 998244353


def solve():
    n = int(input())
    p = [0] * n
    _p = [0] * n
    for i in range(n):
        x, y = map(int, input().split())
        p[i] = x * pow(y, -1, mod) % mod
        _p[i] = (pow(p[i], -1, mod) - 1) % mod

    l = []
    g = [[] for _ in range(n)]
    for _ in range(n - 1):
        u, v = map(int, input().split())
        u -= 1
        v -= 1
        g[u].append(v)
        g[v].append(u)
        l.append((u, v))

    p0 = [0] * n
    p00 = [0] * n
    p1 = [0] * n
    for i in range(n):
        resp = 1
        ress = 0
        for j in g[i]:
            resp = (resp * p[j]) % mod
            ress = (ress + _p[j]) % mod
        p0[i] = resp
        p00[i] = ress
        p1[i] = resp * ress * (1 - p[i]) % mod

    ans1 = 0
    ans2 = 0
    for x in p1:
        ans1 = (ans1 + x) % mod
        ans2 = (ans2 + x**2) % mod
    ans = (ans1**2 - ans2) * pow(2, -1, mod) % mod

    for u, v in l:
        ans -= p1[u] * p1[v]
        ans += p0[u] * p0[v] * _p[u] * _p[v]
        ans %= mod

    for i in range(n):
        ans1 = 0
        ans2 = 0
        for j in g[i]:
            x = p1[j]
            ans1 = (ans1 + x) % mod
            ans2 = (ans2 + x**2) % mod
        ans = (ans - (ans1**2 - ans2) * pow(2, -1, mod)) % mod

        ans1 = 0
        ans2 = 0
        for j in g[i]:
            x = p0[j] * (1 - p[j]) % mod
            ans1 = (ans1 + x) % mod
            ans2 = (ans2 + x**2) % mod
        ans += (ans1**2 - ans2) * pow(2, -1, mod) * (1 - p[i]) * pow(p[i], -2, mod)
        ans %= mod

        ans1 = 0
        ans2 = 0
        for j in g[i]:
            x = p0[j] * (p00[j] - _p[i]) * (1 - p[j]) % mod
            ans1 = (ans1 + x) % mod
            ans2 = (ans2 + x**2) % mod
        ans += (ans1**2 - ans2) * pow(2, -1, mod) * pow(p[i], -1, mod)
        ans %= mod

    return ans


for _ in range(int(input())):
    print(solve())
