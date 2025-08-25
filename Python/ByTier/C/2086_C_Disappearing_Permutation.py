# Contest 2086, Problem C: Disappearing Permutation
# URL: https://codeforces.com/contest/2086/problem/C

import sys

input = lambda: sys.stdin.readline().rstrip()


for _ in range(int(input())):
    n = int(input())
    p = list(map(int, input().split()))
    ew, t = [], 0
    for i in map(int, input().split()):
        c, x = 0, i
        while p[x - 1] != 0:
            y = x - 1
            x, p[y] = p[x - 1], 0
            c += 1
        t += c
        ew.append(t)
    print(" ".join(map(str, ew)))
