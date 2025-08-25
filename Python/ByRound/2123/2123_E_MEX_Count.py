# Contest 2123, Problem E: MEX Count
# URL: https://codeforces.com/contest/2123/problem/E

import sys

input = sys.stdin.readline
for i in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    f = [0] * (n + 1)
    for j in range(n):
        f[a[j]] += 1
    b = []
    for j in range(f.index(0) + 1):
        b.append((f[j], n - j))
    out = [0] * (n + 1)
    for l, r in b:
        out[l] += 1
        if r < n:
            out[r + 1] -= 1
    for j in range(1, n + 1):
        out[j] += out[j - 1]
    print(*out)
