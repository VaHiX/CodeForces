# Contest 2028, Problem C: Alice's Adventures in Cutting Cake
# URL: https://codeforces.com/contest/2028/problem/C

import sys, os, io

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

t = int(input())
ans = []
for _ in range(t):
    n, m, v = map(int, input().split())
    a = [0] + list(map(int, input().split()))
    l, r = [-1] * (m + 1), [-1] * (m + 1)
    l[0], r[0] = 0, n
    u, j = 0, 1
    for i in range(1, n + 1):
        u += a[i]
        if u >= v:
            l[j], u, j = i, 0, j + 1
        if j > m:
            break
    u, j = 0, 1
    for i in range(n, 0, -1):
        u += a[i]
        if u >= v:
            r[j], u, j = i - 1, 0, j + 1
        if j > m:
            break
    for i in range(1, n + 1):
        a[i] += a[i - 1]
    ans0 = -1
    for i in range(m + 1):
        if r[i] ^ -1 and l[m - i] ^ -1:
            ans0 = max(ans0, a[r[i]] - a[l[m - i]])
    ans.append(ans0)
sys.stdout.write("\n".join(map(str, ans)))
