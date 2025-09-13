# Contest 2122, Problem B: Pile Shuffling
# URL: https://codeforces.com/contest/2122/problem/B

import sys

I = sys.stdin.readline
for _ in range(int(I())):
    s = 0
    for _ in range(int(I())):
        a, b, c, d = map(int, I().split())
        s += max(0, a - c) + max(0, b - d) + (b > d) * min(a, c)
    print(s)
