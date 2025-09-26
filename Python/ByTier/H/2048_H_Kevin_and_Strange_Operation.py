# Contest 2048, Problem H: Kevin and Strange Operation
# URL: https://codeforces.com/contest/2048/problem/H


import sys, random, bisect
from collections import deque, defaultdict
from heapq import heapify, heappop, heappush
from itertools import permutations
from math import gcd, log

input = lambda: sys.stdin.readline().rstrip()
mi = lambda: map(int, input().split())
li = lambda: list(mi())

mod = 998244353


def solve_slow(N, S):
    A = [int(s) for s in S] + [1]
    A = A[::-1]

    comp_A = []
    s, n = A[0], 1
    for i in range(1, len(A)):
        if A[i] == s:
            n += 1
        else:
            comp_A.append((s, n))
            s, n = A[i], 1
    comp_A.append((s, n))

    K = len(comp_A)
    dp = [[0] * (N + 1) for i in range(K + 1)]
    for i in range(K)[::-1]:
        s, n = comp_A[i]
        for j in range(N + 1):
            if s == 1:
                dp[i][j] = n + dp[i + 1][j]
            else:
                if n <= j:
                    dp[i][j] = n + dp[i + 1][j]
                else:
                    rest = n - j
                    dp[i][j] = n
                    for k in range(rest + 1):
                        if j + k <= N:
                            dp[i][j] += dp[i + 1][j + k]

    print(dp)
    return dp[0][0]


def solve_fast(N, S):
    A = [int(s) for s in S] + [1]
    A = A[::-1]

    comp_A = []
    s, n = A[0], 1
    for i in range(1, len(A)):
        if A[i] == s:
            n += 1
        else:
            comp_A.append((s, n))
            s, n = A[i], 1
    comp_A.append((s, n))

    K = len(comp_A)
    dp = [0] * (N + 1)
    all_add = 0
    for i in range(K)[::-1]:
        s, n = comp_A[i]

        if s == 1:
            all_add = all_add + n
            all_add %= mod
            continue

        dp[n] = (dp[n] + all_add) % mod
        for j in range(n)[::-1]:
            dp[j] += dp[j + 1] + all_add
            dp[j] %= mod

        for j in range(n + 1):
            dp[j] -= all_add
            dp[j] %= mod

        all_add = all_add + n
        all_add %= mod

    return (dp[0] + all_add - 1) % mod


for _ in range(int(input())):
    S = input()
    N = len(S)
    print(solve_fast(N, S))
