# Contest 2110, Problem C: Racing
# URL: https://codeforces.com/contest/2110/problem/C

import sys

input = sys.stdin.readline
for i in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    s = []
    u, v, f = 0, 0, 1
    for j in range(n):
        l, r = map(int, input().split())
        if a[j] == -1:
            s.append(j)
            v += 1
        elif a[j] == 1:
            u += 1
            v += 1
        while v > r and s:
            a[s.pop()] = 0
            v -= 1
        while u < l and s:
            a[s.pop()] = 1
            u += 1
        if v < u or v > r or u < l:
            f = 0
    for j in range(n):
        if a[j] == -1:
            a[j] = 0
    if f:
        print(*a)
    else:
        print(-1)
