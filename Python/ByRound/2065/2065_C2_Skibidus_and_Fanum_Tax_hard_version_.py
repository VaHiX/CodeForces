# Contest 2065, Problem C2: Skibidus and Fanum Tax (hard version)
# URL: https://codeforces.com/contest/2065/problem/C2

import sys

input = sys.stdin.readline
from bisect import bisect_left as bs

for i in range(int(input())):
    n, m = map(int, input().split())
    a = list(map(int, input().split()))
    b = sorted(list(map(int, input().split())))
    prv = -(1 << 64)
    check = 1
    for j in range(n):
        ind = bs(b, prv + a[j])
        if ind < m:
            if prv <= b[ind] - a[j]:
                if a[j] >= prv:
                    a[j] = min(b[ind] - a[j], a[j])
                else:
                    a[j] = b[ind] - a[j]
            elif a[j] < prv:
                check = 0
                break
        else:
            if a[j] < prv:
                check = 0
                break
        prv = a[j]
    print("yes" if check else "no")
