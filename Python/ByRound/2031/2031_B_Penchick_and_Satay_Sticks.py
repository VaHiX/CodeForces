# Contest 2031, Problem B: Penchick and Satay Sticks
# URL: https://codeforces.com/contest/2031/problem/B

import sys

inp = lambda func=int: list(map(func, sys.stdin.readline().split()))
t = inp()[0]
for _ in range(t):
    n = inp()[0]
    p = inp()
    for i in range(n):
        if p[i] - i > 2 or p[i] < i:
            print("NO")
            break
    else:
        print("YES")
