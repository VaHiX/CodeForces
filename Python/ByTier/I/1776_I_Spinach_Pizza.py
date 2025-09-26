# Contest 1776, Problem I: Spinach Pizza
# URL: https://codeforces.com/contest/1776/problem/I

import sys
from collections import deque

input = sys.stdin.buffer.readline

n = int(input())
x = [0] * (n + 1)
y = [0] * (n + 1)
z = list(range(1, n + 1))
for i in range(1, n + 1):
    x[i], y[i] = map(int, input().split())
turn = 0
if n % 2:
    print("Beatrice")
    turn = 1
else:
    print("Alberto")
sys.stdout.flush()

for i in range(n - 2):
    if i % 2 == turn:
        ans = [0] * len(z)
        for j in range(len(z)):
            a = z[(j + len(z) - 1) % len(z)]
            b = z[j]
            c = z[(j + 1) % len(z)]
            xb = x[b] - x[a]
            xc = x[c] - x[a]
            yb = y[b] - y[a]
            yc = y[c] - y[a]
            ans[j] = abs(xb * yc - xc * yb)
        p = ans.index(min(ans))
        p = z[p]
        print(p)
        z.remove(p)
        sys.stdout.flush()
    else:
        q = int(input())
        z.remove(q)
