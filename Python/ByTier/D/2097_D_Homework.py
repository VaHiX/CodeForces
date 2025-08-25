# Contest 2097, Problem D: Homework
# URL: https://codeforces.com/contest/2097/problem/D


import sys, random, bisect
from collections import deque, defaultdict
from heapq import heapify, heappop, heappush
from itertools import permutations
from math import gcd, log

input = lambda: sys.stdin.readline().rstrip()
mi = lambda: map(int, input().split())
li = lambda: list(mi())


def solve(N, S, T):
    B = N
    while B & 1 == 0:
        B //= 2

    A0 = []
    for i in range(0, N, B):
        A0.append(int(S[i : i + B], 2))
    A1 = []
    for i in range(0, N, B):
        A1.append(int(T[i : i + B], 2))

    def calc_base(X):
        res = []
        for x in X:
            for b in res:
                x = min(x, x ^ b)
            if x != 0:
                res.append(x)
        return res

    base0 = calc_base(A0)
    base1 = calc_base(A1)

    for _ in range(2):
        for b1 in base1:
            for b in base0:
                b1 = min(b1, b1 ^ b)
            if b1 != 0:
                return False
        base0, base1 = base1, base0

    return True


for _ in range(int(input())):
    N = int(input())
    S = input()
    T = input()
    print("Yes" if solve(N, S, T) else "No")
