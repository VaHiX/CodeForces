# Contest 2061, Problem F1: Kevin and Binary String (Easy Version)
# URL: https://codeforces.com/contest/2061/problem/F1

import sys, math, cmath, random
from heapq import heappush, heappop
from bisect import bisect_right, bisect_left
from collections import Counter, deque, defaultdict
from itertools import permutations

# functions #
# MOD = 998244353
MOD = 10**9 + 7
RANDOM = random.randrange(2**62)


def gcd(a, b):
    if a % b == 0:
        return b
    else:
        return gcd(b, a % b)


def lcm(a, b):
    return a // gcd(a, b) * b


def w(x):
    return x ^ RANDOM


##

# String hashing : sh/shclass, fenwick sortedlist : fsortl, Number : numtheory, SparseTable : SparseTable
# bucket sorted list : bsortl, segment tree(lazy propogation) : SegmentTree,Other, bootstrap : bootstrap
# binary indexed tree : BIT, segment tree(point updates) : SegmentPoint, Convex Hull : hull, Trie/Treap : Tries
# Combinatorics : pnc, Diophantine Equations : dpheq, Graphs : graphs, DSU : DSU, Geometry: Geometry, FFT: fft
# Template : https://github.com/OmAmar106/Template-for-Competetive-Programming
# input_file = open(r'input.txt', 'r');sys.stdin = input_file


def solve():
    # L1 = list(map(int, sys.stdin.readline().split()))
    s = sys.stdin.readline().strip()
    t = sys.stdin.readline().strip()
    if s.count("1") != t.count("1"):
        print(-1)
        return
    i = 0
    L = []
    while i < len(s):
        f = s[i]
        count = 0
        while i < len(s) and s[i] == f:
            i += 1
            count += 1
        L.append(count)
    L1 = []
    i = 0
    while i < len(t):
        f = t[i]
        count = 0
        while i < len(t) and t[i] == f:
            i += 1
            count += 1
        L1.append(count)

    i = len(L) - 1
    j = len(L1) - 1
    ans = 0
    if s[-1] != t[-1]:
        f = L.pop()
        ans += 1
        try:
            L[-2] += f
        except:
            L = [f] + L

    # print(L)
    # print(L1)

    while L and L1:
        if L1[-1] < L[-1]:
            print(-1)
            return
        else:
            L1[-1] -= L[-1]
            L.pop()
            if L1[-1] == 0:
                L1.pop()
            else:
                ans += 1
                if len(L) >= 3:
                    L[-3] += L[-1]
                    L.pop()
                else:
                    if len(L) >= 2:
                        L[-1], L[-2] = L[-2], L[-1]
                    else:
                        print(-1)
                        return
        # print(L)
        # print(L1)
    if not L and not L1:
        print(ans)
    else:
        print(-1)


for _ in range(int(sys.stdin.readline().strip())):
    solve()
