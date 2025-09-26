# Contest 2003, Problem D1: Turtle and a MEX Problem (Easy Version)
# URL: https://codeforces.com/contest/2003/problem/D1

import sys
from collections import deque, defaultdict, Counter
t = int(sys.stdin.readline().strip())
for _ in range(t) :
    n, y = map(int, sys.stdin.readline().strip().split())
    x = 0
    for i in range(n) : 
        s = set()
        a = [*map(int, sys.stdin.readline().strip().split())]
        m = a[0]
        s = set(a[1:])
        k = []
        for j in range(m + 2) : 
            if j not in s : 
                k.append(j)
        x = max(k[1], x)
    q = x
    x = min(x, y)
    print((x + 1) * q + (y - x) * (y + x + 1) // 2)