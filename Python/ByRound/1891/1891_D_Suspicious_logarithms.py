# Contest 1891, Problem D: Suspicious logarithms
# URL: https://codeforces.com/contest/1891/problem/D

import sys, os, io

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

q = int(input())
mod = pow(10, 9) + 7
pow2 = [1]
for _ in range(61):
    pow2.append(2 * pow2[-1])
x = []
y = []
for i in range(2, 61):
    l, r = pow2[i], pow2[i + 1]
    l0, r0 = 1, i
    c = 0
    while l0 < r:
        l1, r1 = max(l, l0), min(r, r0)
        if l1 < r1:
            x.append(l1)
            y.append(c)
        l0 *= i
        r0 *= i
        c += 1
ans = []
for _ in range(q):
    l, r = map(int, input().split())
    r += 1
    ans0 = 0
    for i in range(len(x) - 1):
        l1, r1 = max(l, x[i]), min(r, x[i + 1])
        if l1 < r1:
            ans0 += (r1 - l1) % mod * y[i]
    ans0 %= mod
    ans.append(ans0)
sys.stdout.write("\n".join(map(str, ans)))
