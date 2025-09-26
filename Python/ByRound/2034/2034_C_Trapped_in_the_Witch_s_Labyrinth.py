# Contest 2034, Problem C: Trapped in the Witch's Labyrinth
# URL: https://codeforces.com/contest/2034/problem/C

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


for __ in range(fg()):
    n, m = fgh()
    q = deque()
    bad = [[0] * (m + 2) for i in range(n + 2)]
    for i in range(n + 2):
        for j in range(m + 2):
            if i == 0 or j == 0 or (n + 1 - i) == 0 or (m + 1 - j) == 0:
                bad[i][j] = 1
                q.append((i, j))
    a = []
    for i in range(n):
        s = input()[:-1]
        a.append(s)
    m1 = [(-1, 0), (0, 1), (0, -1), (1, 0)]
    d = ["U", "R", "L", "D"]
    while len(q):
        r, c = q.popleft()
        for i in range(4):
            x, y = r - m1[i][0], c - m1[i][1]
            if 0 <= x - 1 < n and 0 <= y - 1 < m and a[x - 1][y - 1] == d[i]:
                if bad[x][y] == 0:
                    q.append((x, y))
                    bad[x][y] = 1
    for i in range(1, n + 1):
        for j in range(1, m + 1):
            for u in m1:
                if bad[i - u[0]][j - u[1]] == 0:
                    break
            else:
                bad[i][j] = 1
    s = 0
    for i in range(n + 2):
        for j in range(m + 2):
            if bad[i][j] == 0:
                s += 1
    print(s)
