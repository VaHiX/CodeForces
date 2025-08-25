# Contest 2132, Problem E: Arithmetics Competition
# URL: https://codeforces.com/contest/2132/problem/E

import sys
from collections import defaultdict, deque, Counter
from heapq import heappush, heappop, heapify
from math import inf, comb, ceil, log, lcm, gcd, isqrt
from functools import cache
from itertools import accumulate, combinations, permutations, groupby
from bisect import bisect_left, bisect_right, insort_left
from random import randint, randrange
from time import time_ns

# from sortedcontainers import SortedList
input = lambda: sys.stdin.readline().rstrip()
inp = lambda: list(map(int, input().split()))
I = lambda: int(input())

xor = randint(1, 15612)


for _ in range(I()):
    n, m, q = inp()
    a = inp()
    b = inp()
    a.sort(reverse=1)
    b.sort(reverse=1)
    psa = [0] + list(accumulate(a))

    psb = [0] + list(accumulate(b))
    for __ in range(q):
        x, y, z = inp()
        lo = max(0, z - y) - 1
        hi = min(x, z)

        while hi - lo > 1:
            mid = lo + hi >> 1
            if psa[mid] + psb[z - mid] <= psa[mid + 1] + psb[z - mid - 1]:
                lo = mid
            else:
                hi = mid
        print(psa[hi] + psb[z - hi])
