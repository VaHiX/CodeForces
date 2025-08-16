# Contest 2127, Problem G1: Inter Active (Easy Version)
# URL: https://codeforces.com/contest/2127/problem/G1

import os
import random
import sys
from typing import *
from collections import defaultdict, Counter, deque
from functools import cache, reduce
from itertools import pairwise, combinations, permutations, groupby, accumulate
from bisect import bisect_left, bisect_right, insort_left, insort_right
from heapq import *
from math import gcd, lcm, isqrt
from operator import add, sub, mul, floordiv, truediv, and_, or_, xor

from types import GeneratorType

def bootstrap(f, stack=[]):
    def wrappedfunc(*args, **kwargs):
        if stack:
            return f(*args, **kwargs)
        else:
            to = f(*args, **kwargs)
            while True:
                if type(to) is GeneratorType:
                    stack.append(to)
                    to = next(to)
                else:
                    stack.pop()
                    if not stack:
                        break
                    to = stack[-1].send(to)
            return to

    return wrappedfunc


input = sys.stdin.readline
output = lambda x: sys.stdout.write(str(x) + "\n")
outputL = lambda x: sys.stdout.write(" ".join(map(str, x)) + "\n")


I = lambda: input().rstrip("\n")
II = lambda: int(input())
MII = lambda: map(int, input().split())
LMII = lambda: list(MII())
TMII = lambda: tuple(MII())
LI = lambda: list(I())
LSI = lambda: list(map(int, I()))

def query(a):
    for i in range(len(a)):
        a[i] += 1
    print("?", *a, flush=True)
    return II()

def answer(a):
    for i in range(len(a)):
        a[i] += 1
    print("!", *a, flush=True)

def solve():
    n = II()
    k = n // 4
    print(n // 4 + 1, flush=True)
    ans = [0] * n
    for i in range(n):
        cand = list(range(n))
        cand.remove(i)
        left, right = 0, len(cand) - 1
        while left < right:
            mid = (left + right) // 2
            diff = list()
            same = list()
            b = [-1] * n
            b[k] = i
            for j in range(n):
                if j != k:
                    if k < j <= n - k - 1:
                        same.append(j)
                    else:
                        diff.append(j)
            while mid - left + 1 > len(diff):
                mid -= 1
            for j in range(left, mid + 1):
                b[diff[j - left]] = cand[j]
            for j in range(mid + 1, right + 1):
                b[same[j - mid - 1]] = cand[j]
            s = set(b)
            pos = list()
            for j in range(n):
                if b[j] == -1:
                    pos.append(j)
            for j in range(n):
                if j not in s:
                    b[pos.pop()] = j
            assert max(b) == n - 1
            assert min(b) == 0
            p = query(b[:])
            for j in range(len(diff) // 2):
                b[diff[j]], b[diff[-j - 1]] = b[diff[-j - 1]], b[diff[j]]
            for j in range(len(same) // 2):
                b[same[j]], b[same[-j - 1]] = b[same[-j - 1]], b[same[j]]
            p += query(b[:])
            if p == n - 1:
                right = mid
            else:
                left = mid + 1
        ans[cand[left]] = i
    answer(ans)

TC = II()

def main():
    for _ in range(TC):
        solve()

main()