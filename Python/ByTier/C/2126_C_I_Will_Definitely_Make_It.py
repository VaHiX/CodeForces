# Contest 2126, Problem C: I Will Definitely Make It
# URL: https://codeforces.com/contest/2126/problem/C

import sys

I = sys.stdin.readline
for _ in range(int(I())):
    n, k = map(int, I().split())
    l = [*map(int, I().split())]
    s = l[k - 1]
    l.sort()
    w = 0
    f = 1
    for e in l:
        if e > s:
            w += e - s
            if w > s:
                print("NO")
                f = 0
                break
            s = e
    if f:
        print("YES")
