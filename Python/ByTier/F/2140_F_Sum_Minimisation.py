# Contest 2140, Problem F: Sum Minimisation
# URL: https://codeforces.com/contest/2140/problem/F

import sys
import random
import math
from collections import deque

input = sys.stdin.readline


def fg():
    return int(input())


def fgh():
    return [int(xx) for xx in input().split()]


def df():
    print("No")


def sd():
    print("Yes")


def good(a):
    fl = 1
    for i in range(2, len(a)):
        d = []
        for j in range(len(a)):
            d.append(a[j] % i)
        if len(set(d)) >= 2:
            fl = 0
            break
    if fl:
        if sum(a) % len(a) == 0:
            return True
    return False


for __ in range(fg()):
    n = fg()
    a = fgh()
    if n >= 100:
        if len(set(a)) == 1:
            print(a[0] * n)
        else:
            print(-1)
    else:
        if n == 1:
            print(a[0])
            continue
        if n == 2:
            print((a[0] + a[1]) - (a[0] + a[1]) % 2)
        else:
            if good(a):
                print(sum(a))
                continue
            if (sum(a) % n) != 1:
                print(-1)
                continue
            a.sort()
            if not good(a[1:]):
                print(-1)
                continue
            if sum(a) % n != 1:
                print(-1)
                continue
            t = 0
            for i in range(2, n):
                if (a[0] + (i - 1) * a[1]) % i > 1:
                    t = 1
            if t:
                print(-1)
                continue
            a[0] -= 1
            fl = 1
            for i in range(2, n):
                d = []
                for j in range(n):
                    d.append(a[j] % i)
                if len(set(d)) >= 2:
                    fl = 0
                    break
            if fl:
                print(sum(a))
            else:
                print(-1)
