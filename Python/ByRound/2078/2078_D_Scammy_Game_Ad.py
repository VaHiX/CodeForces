# Contest 2078, Problem D: Scammy Game Ad
# URL: https://codeforces.com/contest/2078/problem/D

import sys

input = sys.stdin.readline

for _ in range(int(input())):
    n = int(input())
    a = []
    for _ in range(n):
        b, c, d, e = input().split()
        a.append((b, int(c), d, int(e)))
    l, r, k = 1, 1, 0
    for b, c, d, e in a[::-1]:
        m = max(l, r)
        if b == "x":
            l += (c - 1) * m
        else:
            k += c * m
        if d == "x":
            r += (e - 1) * m
        else:
            k += e * m
    print(k + l + r)
