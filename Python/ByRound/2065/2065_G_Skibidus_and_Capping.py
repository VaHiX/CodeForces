# Contest 2065, Problem G: Skibidus and Capping
# URL: https://codeforces.com/contest/2065/problem/G

from sys import stdin

R = stdin.readline
S = lambda: map(int, R().split())
P = print

M = 200000
p = [0, 0] + [1] * (M - 1)
for i in range(2, int(M**0.5) + 1):
    if p[i]:
        p[2 * i :: i] = [0] * (M // i - 1)
q = [i for i in range(M + 1) if p[i]]
l = len(q)
for i in range(l):
    for j in range(i, l):
        if q[i] * q[j] > M:
            break
        p[q[i] * q[j]] = q[i]
r = [i for i in range(M + 1) if p[i] > 1]
m = len(r)
for _ in range(int(R())):
    n = int(R())
    c = [0] * (n + 1)
    u, z = 0, 0
    for x in S():
        u += p[x] == 1
        c[x] += 1
    for i in range(l):
        if q[i] > n:
            break
        u -= c[q[i]]
        z += c[q[i]] * u
    for i in range(len(r)):
        a, b = r[i], p[r[i]]
        if a > n:
            break
        z += c[a] * c[b] + c[a] * (c[a] + 1) // 2
        if b * b != a:
            z += c[a] * c[a // b]
    P(z)
