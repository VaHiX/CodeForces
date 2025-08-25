# Contest 2132, Problem D: From 1 to Infinity
# URL: https://codeforces.com/contest/2132/problem/D

import sys

I = sys.stdin.readline

P = [1]

for tc in range(19):
    P += [P[-1] * 10]


def S(n):
    a = 0
    p = 1
    while p <= n:
        h = n // (p * 10)
        c = (n // p) % 10
        l = n % p
        a += h * 45 * p + (c * (c - 1) // 2) * p + c * (l + 1)
        p *= 10
    return a


T = [0] + [S(P[i] - 1) - S(P[i - 1] - 1) for i in range(1, 19)]

for _ in range(int(I())):
    k = int(I())
    ans = 0
    d = 1

    while 1:
        c = 9 * P[d - 1]
        t = c * d
        if k > t:
            ans += T[d]
            k -= t
            d += 1
            continue
        q, r = divmod(k, d)
        x = P[d - 1]

        if q:
            ans += S(x + q - 1) - S(x - 1)
        if r:
            ans += sum(map(int, str(x + q)[:r]))
        print(ans)
        break
