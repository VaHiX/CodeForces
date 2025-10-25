# Contest 2055, Problem C: The Trail
# URL: https://codeforces.com/contest/2055/problem/C

import sys
import math

input = sys.stdin.readline
for _ in range(int(input())):
    n, m = list(map(int, input().split()))
    s = input().rstrip()
    l = []
    for i in range(n):
        x = list(map(int, input().split()))
        l.append(x)
    a, b = 0, 0
    for i in s:
        if i == "D":
            t = sum(l[a])
            l[a][b] = -t
            a += 1
        elif i == "R":
            t = 0
            for j in range(n):
                t += l[j][b]
            l[a][b] = -t
            b += 1
    t = sum(l[a])
    l[a][b] = -t
    for i in range(n):
        print(*l[i])
