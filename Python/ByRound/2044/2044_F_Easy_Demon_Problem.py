# Contest 2044, Problem F: Easy Demon Problem
# URL: https://codeforces.com/contest/2044/problem/F

from sys import stdin

R = stdin.readline
S = lambda: map(int, R().split())
P = print
from bisect import bisect_left as bil

n, m, q = S()
a = [*S()]
b = [*S()]
x, y = sum(a), sum(b)
M = 200000
u = [0] * (2 * M + 1)
v = [0] * (2 * M + 1)
for z in a:
    if 0 < abs(x - z) <= M:
        u[x - z] = 1
for z in b:
    if 0 < abs(y - z) <= M:
        v[y - z] = 1
u = [i for i in range(-M, M + 1) if u[i]]
v = [i for i in range(-M, M + 1) if v[i]]
p = [0] * (2 * M + 1)
for k in u:
    z = abs(k)
    for i in range(bil(v, -M // z), bil(v, M // z + 1)):
        if abs(k * v[i]) <= M:
            p[k * v[i]] = 1
for _ in range(q):
    P("YES" if p[int(R())] else "NO")
