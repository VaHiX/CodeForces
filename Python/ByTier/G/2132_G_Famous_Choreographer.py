# Contest 2132, Problem G: Famous Choreographer
# URL: https://codeforces.com/contest/2132/problem/G

import sys

input = sys.stdin.readline
Q = int(input())
from random import randint

for _ in range(Q):
    N, M = map(int, input().split())
    S = [input()[:-1] for i in range(N)]
    mod = 10**9 + 7
    mod2 = 998244353
    result = 10**10
    F = randint(1004, 10678)
    u00 = [1] * (N * M + 1)
    u01 = [1] * (N * M + 1)
    u10 = [1] * (N * M + 1)
    u11 = [1] * (N * M + 1)
    K = randint(10890, 56789)
    for i in range(1, N * M + 1):
        u00[i] = u00[i - 1] * F
        u00[i] %= mod
        u01[i] = u01[i - 1] * F
        u01[i] %= mod2
        u11[i] = u11[i - 1] * K
        u11[i] %= mod2
        u10[i] = u10[i - 1] * K
        u10[i] %= mod
    v0 = [[0] * M for i in range(N)]
    v1 = [[0] * M for i in range(N)]
    for i in range(N):
        for j in range(M):
            x = ord(S[i][j]) - ord("a") + 1
            v0[i][j] = v0[i][j - 1] * F + x
            v0[i][j] %= mod
            v1[i][j] = v1[i][j - 1] + x * u00[j]
            v1[i][j] %= mod
    for j in range(M):
        ans0 = 0
        ans1 = 0
        for i in range(N):
            ans0 = ans0 * K + v0[i][j]
            ans0 %= mod
            ans1 += v1[i][j] * u10[i]
            ans1 %= mod
            if ans0 == ans1:
                a = N - 1 - i
                b = M - 1 - j
                result = min(result, (N + a) * (M + b))
    for j in range(M):
        ans0, ans1 = 0, 0
        for i in range(N - 1, -1, -1):
            ans0 = ans0 * K + v0[i][j]
            ans0 %= mod
            ans1 += v1[i][j] * u10[N - 1 - i]
            ans1 %= mod
            if ans0 == ans1:
                a = i
                b = M - 1 - j
                result = min(result, (N + a) * (M + b))
    for i in range(N):
        S[i] = S[i][::-1]
    v0 = [[0] * M for i in range(N)]
    v1 = [[0] * M for i in range(N)]
    for i in range(N):
        for j in range(M):
            x = ord(S[i][j]) - ord("a") + 1
            v0[i][j] = v0[i][j - 1] * F + x
            v0[i][j] %= mod
            v1[i][j] = v1[i][j - 1] + x * u00[j]
            v1[i][j] %= mod
    for j in range(M):
        ans0 = 0
        ans1 = 0
        for i in range(N):
            ans0 = ans0 * K + v0[i][j]
            ans0 %= mod
            ans1 += v1[i][j] * u10[i]
            ans1 %= mod
            if ans0 == ans1:
                a = N - 1 - i
                b = M - 1 - j
                result = min(result, (N + a) * (M + b))
    for j in range(M):
        ans0, ans1 = 0, 0
        for i in range(N - 1, -1, -1):
            ans0 = ans0 * K + v0[i][j]
            ans0 %= mod
            ans1 += v1[i][j] * u10[N - 1 - i]
            ans1 %= mod
            if ans0 == ans1:
                a = i
                b = M - 1 - j
                result = min(result, (N + a) * (M + b))
    print(result - N * M)
