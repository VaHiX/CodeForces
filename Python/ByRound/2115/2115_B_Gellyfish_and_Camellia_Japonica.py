# Contest 2115, Problem B: Gellyfish and Camellia Japonica
# URL: https://codeforces.com/contest/2115/problem/B

import sys

input = sys.stdin.readline

from math import gcd

out = []

t = int(input())
for _ in range(t):
    n, q = map(int, input().split())
    b = list(map(int, input().split()))

    x = []
    y = []
    z = []
    for _ in range(q):
        xi, yi, zi = map(int, input().split())
        xi -= 1
        yi -= 1
        zi -= 1

        x.append(xi)
        y.append(yi)
        z.append(zi)

    a = b[:]
    for i in range(q)[::-1]:
        xi, yi, zi = x[i], y[i], z[i]

        old = a[zi]
        a[zi] = 0

        a[xi] = max(a[xi], old)  # Sus
        a[yi] = max(a[yi], old)

    c = a[:]
    for i in range(q):
        xi, yi, zi = x[i], y[i], z[i]

        c[zi] = min(c[xi], c[yi])

    if c == b:
        out.append(" ".join(map(str, a)))
    else:
        out.append("-1")

print("\n".join(out))
