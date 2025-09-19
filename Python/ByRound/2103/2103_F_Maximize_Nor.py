# Contest 2103, Problem F: Maximize Nor
# URL: https://codeforces.com/contest/2103/problem/F

import sys
import heapq
import math
import random
from itertools import *
from collections import deque

input = sys.stdin.readline


def fg():
    return int(input())


def fgh():
    return [int(xx) for xx in input().split()]


def tt():
    sys.stdout.flush()


def sd():
    print("Yes")


def df():
    print("No")


step = [1]
for i in range(20):
    step.append(step[-1] * 2)


def nor(x, b):
    global k
    return (2**k - 1) ^ (x | b)


def nor1(a):
    if len(a) == 1:
        return a[0]
    return nor(nor1(a[: len(a) - 1]), a[-1])


for __ in range(fg()):
    n, k = fgh()
    a = fgh()
    if n == 1:
        print(a[0])
        continue
    ans = a[:]
    for i in range(n - 1):
        ans[i] = max(ans[i], nor(a[i], a[i + 1]))
        ans[i + 1] = max(ans[i + 1], nor(a[i + 1], a[i]))
    pr = [a[0]]
    for i in range(1, n):
        pr.append(nor(pr[-1], a[i]))
    mx = pr[-1]
    for i in range(n - 1, -1, -1):
        mx = max(mx, pr[i])
        ans[i] = max(ans[i], mx)
    pr = [a[1]]
    for i in range(2, n):
        pr.append(nor(pr[-1], a[i]))
    mx = pr[-1]
    for i in range(n - 1, 0, -1):
        mx = max(mx, pr[i - 1])
        ans[i] = max(ans[i], mx)
    for i in range(n - 1):
        for j in range(k):
            if a[i] & step[j]:
                pr = [a[i]]
                L = -1
                for l in range(i + 1, n + 1):
                    if l == n or (a[l] & step[j]):
                        L = l
                        break
                    pr.append(nor(pr[-1], a[l]))
                mx = pr[-1]
                for o in range(L - 1, i - 1, -1):
                    mx = max(mx, pr[o - i])
                    ans[o] = max(ans[o], mx)
                if L > i + 1:
                    pr = [a[i + 1]]
                    for l in range(i + 2, n + 1):
                        if l == n or (a[l] & step[j]):
                            break
                        pr.append(nor(pr[-1], a[l]))
                    mx = pr[-1]
                    for o in range(L - 1, i, -1):
                        mx = max(mx, pr[o - i - 1])
                        ans[o] = max(ans[o], mx)
                if L > i + 2:
                    pr = [a[i + 2]]
                    for l in range(i + 3, n + 1):
                        if l == n or (a[l] & step[j]):
                            break
                        pr.append(nor(pr[-1], a[l]))
                    mx = pr[-1]
                    for o in range(L - 1, i + 1, -1):
                        mx = max(mx, pr[o - i - 2])
                        ans[o] = max(ans[o], mx)

    print(*ans)
