# Contest 50, Problem C: Happy Farm 5
# URL: https://codeforces.com/contest/50/problem/C

import os, sys

if os.path.exists("input.txt"):
    sys.stdin = open("input.txt", "rt")
I = sys.stdin.readline

n = int(I())
M = 2**31
a, b, c, d = -M, M, -M, M
for _ in range(n):
    x, y = map(int, I().split())
    a = max(a, x + y)
    b = min(b, x + y)
    c = max(c, x - y)
    d = min(d, x - y)
print(a - b + c - d + 4)
