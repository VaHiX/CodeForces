# Contest 4, Problem D: Mysterious Present
# URL: https://codeforces.com/contest/4/problem/D

import sys

I = lambda: map(int, sys.stdin.readline().split())
from bisect import bisect

n, w, h = I()
A = [(0, 0)]
P = [(w, -h, 0)]
for i in range(n):
    x, y = I()
    P.append((x, -y, i + 1))
P.sort(reverse=1)
Q = [0] * (n + 1)
for x, y, i in P:
    k = bisect(A, (y, 0))
    if x == w and y == -h:
        print(k)
        if k:
            O = []
            c = A[k - 1][1]
            while c:
                O.append(c)
                c = Q[c]
            print(*O)
        break
    if k:
        Q[i] = A[k - 1][1]
    if k == len(A):
        A.append((y, i))
    else:
        A[k] = (y, i)
