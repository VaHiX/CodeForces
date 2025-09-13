# Contest 2113, Problem F: Two Arrays
# URL: https://codeforces.com/contest/2113/problem/F

# from typing import List
# from copy import deepcopy
# from heapq import heapify,heappop,heappush
# from functools import cache,lru_cache,reduce
# from random import getrandbits,randint,shuffle
# from collections import Counter,deque,defaultdict
# from string import ascii_lowercase,ascii_uppercase,digits
# from itertools import accumulate,combinations,permutations
# from bisect import bisect_left,bisect_right # left:>=x, right:>x
# from math import ceil,floor,sqrt,pi,factorial,gcd,log,log10,log2,comb
# from sortedcontainers import SortedList
# from fractions import Fraction

# r=getrandbits(30)
# mod=10**9+7
# mod=998244353
# invmod=lambda x: pow(x,mod-2,mod) # gcd(x,mod)==1; mod-2:cnt(gcd(mod)==1)
max2 = lambda x, y: x if x > y else y
min2 = lambda x, y: y if x > y else x
# PY = lambda : print("Yes")
# PN = lambda : print("No")

from sys import stdin, setrecursionlimit

# setrecursionlimit(200000)
input = lambda: stdin.readline().rstrip()
ls = lambda: map(int, input().split())
ln = lambda: int(input())
lnums = lambda: list(map(int, input().split()))


def slv():
    n = ln()
    # n,k=ls()
    # m,n=ls()
    # s=input()
    # nums=lnums()
    # n,nums=ln(),lnums()
    # matrix = [lnums() for i in range(m)]
    # matrix = [input().split() for i in range(m)]
    a, b = lnums(), lnums()
    f = [0] * (2 * n + 1)
    g = [0] * n

    def upd(x, t):
        if f[x] == 0:
            f[x] = t
        elif f[x] == 3 - t:
            f[x] = 3

    pos = [[] for i in range(2 * n + 1)]
    vis = [0] * (2 * n + 1)
    l = [len(x) for x in pos]
    for i, (x, y) in enumerate(zip(a, b)):
        pos[x].append(i)
        pos[y].append(i)
    q = list(range(n))
    tmp = []
    while q:
        i = q.pop()
        if g[i]:
            continue
        g[i] = 1
        x, y = a[i], b[i]
        if x == y or f[x] == f[y] == 3:
            f[x] = 3
        elif (f[x] == 3 and f[y] == 0) or (f[x] == 0 and f[y] == 3):
            tmp.append(i)
            g[i] = 0
            continue
        elif f[x] == 1 or f[y] == 2:
            a[i], b[i] = y, x
            upd(x, 2)
            upd(y, 1)
        else:
            upd(x, 1)
            upd(y, 2)
        if not vis[x]:
            q.extend(pos[x])
            vis[x] = 1
        if not vis[y]:
            q.extend(pos[y])
            vis[y] = 1
    q = tmp
    while q:
        i = q.pop()
        if g[i]:
            continue
        g[i] = 1
        x, y = a[i], b[i]
        if x == y or f[x] == f[y] == 3:
            f[x] = 3
        elif f[x] == 1 or f[y] == 2:
            a[i], b[i] = y, x
            upd(x, 2)
            upd(y, 1)
        else:
            upd(x, 1)
            upd(y, 2)
        if not vis[x]:
            q.extend(pos[x])
            vis[x] = 1
        if not vis[y]:
            q.extend(pos[y])
            vis[y] = 1
    z = 0
    for x in f:
        z += (x + 1) >> 1
    print(z)
    print(*a)
    print(*b)
    return


for ii in range(ln()):
    a = slv()
    # print(a)
