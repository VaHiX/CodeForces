# Contest 2048, Problem G: Kevin and Matrices
# URL: https://codeforces.com/contest/2048/problem/G

from sys import stdin, stdout

# from os import _exit
# from bisect import bisect_left,bisect
# from heapq import heapify,heappop,heappush
# from sys import setrecursionlimit
# from collections import defaultdict,Counter,deque
from itertools import permutations, accumulate

# from math import gcd,ceil,sqrt,factorial
# from functools import lru_cache
# setrecursionlimit(int(1e5))
input, print = stdin.readline, stdout.write

MOD = mod = 998244353

N = int(1e6) + 5

(*fac,) = accumulate(range(1, N + 1), lambda p, x: p * x % mod, initial=1)
(*invfac,) = accumulate(
    range(N, 0, -1), lambda p, x: p * x % mod, initial=pow(fac[-1], -1, mod)
)
invfac.reverse()


def sum(I):
    tot = 0
    for x in I:
        tot = (tot + x) % mod
    return tot


def pow(b, p, m):
    r = 1
    while p:
        if p & 1:
            r = (r * b) % m
        p >>= 1
        b = (b * b) % m
    return r


def ncr(n, r):
    return (fac[n] * invfac[r] * invfac[n - r]) % mod


t = int(input())
for _ in range(t):
    n, m, v = list(map(int, input().split()))
    ans = sum(
        sum(
            (-1) ** i
            * ncr(n, i)
            * (
                pow(
                    (-pow(v - k + 1, n - i, mod) + pow(k, i, mod) * pow(v, n - i, mod))
                    % mod,
                    m,
                    mod,
                )
                - pow((pow(k, i, mod) * pow(v, n - i, mod)) % mod, m, mod)
            )
            % mod
            for i in range(1, n + 1)
        )
        for k in range(1, v + 1)
    )
    print(f"{ans}\n")
