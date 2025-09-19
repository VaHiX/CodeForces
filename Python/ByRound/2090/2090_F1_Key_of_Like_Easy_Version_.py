# Contest 2090, Problem F1: Key of Like (Easy Version)
# URL: https://codeforces.com/contest/2090/problem/F1

import sys

input = sys.stdin.readline
MOD = 10**9 + 7
for _ in range(int(input())):
    n, l, k = map(int, input().split())
    tot = l
    mov = [0] * n
    mov[0] = 1
    out = [0] * n
    for i in range(l, 0, -1):
        p = pow(i, -1, MOD)
        i %= n
        if i == 0:
            break
        nex = [0] * n
        for u in range(n):
            for j in range(1, i + 1):
                nex[u] += mov[u - j] * p
                nex[u] %= MOD
        mov = nex
        for i in range(n):
            out[i - 1] += mov[i]
    for i in range(n):
        out[i] %= MOD
    ex = tot - sum(out)
    ex %= MOD
    ex *= pow(n, -1, MOD)
    ex %= MOD
    for i in range(n):
        out[i] += ex
        out[i] %= MOD
    print(*out)
