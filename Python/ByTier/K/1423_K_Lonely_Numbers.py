# Contest 1423, Problem K: Lonely Numbers
# URL: https://codeforces.com/contest/1423/problem/K

# Created by Ketan_Raut
# Copyright © 2024 iN_siDious. All rights reserved.
import sys, os
import random
from math import *
from string import ascii_lowercase, ascii_uppercase
from collections import Counter, defaultdict, deque
from itertools import accumulate, combinations, permutations
from heapq import heappushpop, heapify, heappop, heappush
from bisect import bisect_left, bisect_right
from types import GeneratorType
from random import randint

RANDOM = randint(1, 10**10)


class op(int):
    def __init__(self, x):
        int.__init__(x)

    def __hash__(self):
        return super(op, self).__hash__() ^ RANDOM


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


inp = lambda: sys.stdin.buffer.readline().decode().strip()
out = sys.stdout.write


def S():
    return inp()


def I():
    return int(inp())


def F():
    return float(inp())


def MI():
    return map(int, inp().split())


def MF():
    return map(float, inp().split())


def MS():
    return inp().split()


def LS():
    return list(inp().split())


def LI():
    return list(map(int, inp().split()))


def LF():
    return list(map(float, inp().split()))


def Query(i, j):
    print3("?", i, j)
    sys.stdout.flush()
    qi = I()
    return qi


def print1(x):
    return out(str(x) + "\n")


def print2(x, y):
    return out(str(x) + " " + str(y) + "\n")


def print3(x, y, z):
    return out(str(x) + " " + str(y) + " " + str(z) + "\n")


def print_arr(arr):
    for num in arr:
        out(str(num) + " ")
    out(str("\n"))


MAX = 10**6 + 10
is_prime = [1] * MAX
is_prime[0], is_prime[1] = 0, 0


def Sieve(n):
    global is_prime
    p = 2
    while p * p <= n:
        if is_prime[p] == 1:
            for i in range(p * p, n + 1, p):
                is_prime[i] = 0
        p += 1


Sieve(MAX - 2)
gg = [0] * (MAX - 1)
for i in range(2, MAX - 1):
    gg[i] += gg[i - 1]
    if not is_prime[i]:
        gg[i] += 1
        continue
    if i * i < MAX - 1:
        gg[i * i] += 1
for _ in range(1):
    t = I()
    arr = LI()
    ans = [i - gg[i] for i in arr]
    for c in ans:
        print1(c)
