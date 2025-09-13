# Contest 2038, Problem F: Alternative Platforms
# URL: https://codeforces.com/contest/2038/problem/F

import sys
import math

mod = 998244353
G = 3
GI = (mod + 1) // 3


def qpow(a, b):
    c = 1
    while b > 0:
        if b & 1:
            c = c * a % mod
        a = a * a % mod
        b >>= 1
    return c


def init(n):
    L = 1
    while L <= n:
        L <<= 1
    lb = [0] * L
    for i in range(L):
        lb[i] = (lb[i >> 1] >> 1) | ((i & 1) and (L >> 1) or 0)
    return L, lb


def NTT(a, fl, L, lb):
    for i in range(L):
        if i < lb[i]:
            a[i], a[lb[i]] = a[lb[i]], a[i]
    o = 1
    while o < L:
        Wn = qpow(G if fl else GI, (mod - 1) // (o << 1))
        for i in range(0, L, o << 1):
            w = 1
            for j in range(o):
                x = a[i + j]
                y = a[i + j + o] * w % mod
                a[i + j] = (x + y) % mod
                a[i + j + o] = (x - y) % mod
                w = w * Wn % mod
        o <<= 1
    if not fl:
        inv_L = qpow(L, mod - 2)
        for i in range(L):
            a[i] = a[i] * inv_L % mod


def C(a, b, jc, ij):
    return jc[a] * ij[b] % mod * ij[a - b] % mod


def Sol(c, n, tp, jc, ij, ans):
    c_sorted = sorted(c[1 : n + 1])
    c_sorted.insert(0, 0)

    max_len = 1
    while max_len <= 2 * n:
        max_len <<= 1
    e = [0] * max_len
    f = [0] * max_len

    for i in range(1, n + 1):
        e[n - i + 1] = jc[n - i + 1] * (c_sorted[i] - c_sorted[i - 1]) % mod

    for i in range(n // 2 + 1):
        e[i], e[n - i] = e[n - i], e[i]

    for i in range(n + 1):
        f[i] = ij[i]

    L, lb_arr = init(2 * n)
    NTT(e, 1, L, lb_arr)
    NTT(f, 1, L, lb_arr)
    for i in range(L):
        e[i] = e[i] * f[i] % mod
    NTT(e, 0, L, lb_arr)

    for i in range(n + 1):
        ans[i] = (ans[i] + tp * ij[i] * e[n - i]) % mod


n = int(sys.stdin.readline())
a = list(map(int, sys.stdin.readline().split()))
b = list(map(int, sys.stdin.readline().split()))

jc = [1] * (n + 1)
ij = [1] * (n + 1)
for i in range(1, n + 1):
    jc[i] = i * jc[i - 1] % mod
    ij[i] = qpow(jc[i], mod - 2)

a = [0] + a
b = [0] + b
c = [0] * (n + 1)
ans = [0] * (n + 1)

for i in range(1, n + 1):
    c[i] = a[i]
Sol(c, n, 1, jc, ij, ans)

for i in range(1, n + 1):
    c[i] = b[i]
Sol(c, n, 1, jc, ij, ans)

for i in range(1, n + 1):
    c[i] = min(a[i], b[i])
Sol(c, n, -1, jc, ij, ans)

result = []
for i in range(1, n + 1):
    inv_C = qpow(C(n, i, jc, ij), mod - 2)
    res = (ans[i] * inv_C % mod + mod) % mod
    result.append(str(res))
print(" ".join(result))
