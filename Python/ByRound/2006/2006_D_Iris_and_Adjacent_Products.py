# Contest 2006, Problem D: Iris and Adjacent Products
# URL: https://codeforces.com/contest/2006/problem/D

import math
import sys, os, io
input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

def f(u, v, w):
    return u << 40 ^ v << 20 ^ w

t = int(input())
ans = []
for _ in range(t):
    n, q, k = map(int, input().split())
    b = [0] + list(map(int, input().split()))
    m = int(math.sqrt(k))
    for i in range(1, n + 1):
        if b[i] > m:
            b[i] = k // b[i] + m
    l0, r0, q0 = [0] * q, [0] * q, [0] * q
    m1 = 357
    for i in range(q):
        l, r = map(int, input().split())
        l1 = (l - 1) // m1
        r1 = r if not l1 & 1 else n - r
        l0[i], r0[i], q0[i] = l, r, f(l1, r1, i)
    l, r = 1, 0
    cnt = [0] * (2 * m + 1)
    ans0, q0 = [0] * q, [i & 0xfffff for i in sorted(q0)]
    for i in q0:
        l1, r1 = l0[i], r0[i]
        while l1 < l:
            l -= 1
            cnt[b[l]] += 1
        while r < r1:
            r += 1
            cnt[b[r]] += 1
        while l < l1:
            cnt[b[l]] -= 1
            l += 1
        while r1 < r:
            cnt[b[r]] -= 1
            r -= 1
        u, v, ans1 = 0, 0, 0
        for j in range(1, m + 1):
            c = max((v - u + cnt[j + m] - cnt[j] + 1) >> 1, 0)
            ans1 += c
            u += cnt[j] + c
            v += cnt[j + m] - c
            if u + v == r - l + 1:
                if u > v and c:
                    ans1 -= 1
                break
        ans0[i] = ans1
    ans.append(" ".join(map(str, ans0)))
sys.stdout.write("\n".join(ans))