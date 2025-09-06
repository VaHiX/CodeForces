# Contest 2038, Problem C: DIY
# URL: https://codeforces.com/contest/2038/problem/C

import sys
input = sys.stdin.readline


for _ in range(int(input())):
    n = int(input())
    w = sorted(map(int, input().split())) + [10**10]
    c = 0
    d = []
    for i in range(n):
        c += 1
        if w[i] != w[i+1]:
            for a in range(c//2):
                d.append(w[i])
            c = 0

    if len(d) > 3:
        print('YES')
        print(d[0], d[1], d[0], d[-1], d[-2], d[1], d[-2], d[-1])
    else:
        print('NO')
