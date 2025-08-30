# Contest 2113, Problem D: Cheater
# URL: https://codeforces.com/contest/2113/problem/D

import sys

input = sys.stdin.readline
for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    lo = 0
    hi = n + 1
    while lo + 1 < hi:
        mid = (lo + hi) // 2
        premin = 2 * n + 1
        for i in range(n - mid + 1):
            premin = min(premin, b[i])
        smol = 0
        for j in range(mid):
            if a[j] < premin:
                smol += 1
        big = 0
        for j in range(mid, n):
            if a[j] > premin:
                big += 1
        if smol <= 1 and big >= smol:
            lo = mid
        else:
            hi = mid
    print(lo)
