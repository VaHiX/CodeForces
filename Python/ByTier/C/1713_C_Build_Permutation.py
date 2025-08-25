# Contest 1713, Problem C: Build Permutation
# URL: https://codeforces.com/contest/1713/problem/C

import math
from sys import stdin

for _ in range(int(stdin.readline().strip())):
    n = int(stdin.readline().strip())
    a, t = [0] * n, n - 1
    while True:
        ns = math.ceil(math.sqrt(t)) ** 2
        for i in range(ns - t, t + 1):
            a[i] = ns - i
        t = ns - t - 1
        if t < 0:
            break
    print(*a)
