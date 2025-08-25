# Contest 2111, Problem B: Fibonacci Cubes
# URL: https://codeforces.com/contest/2111/problem/B

import sys

input = sys.stdin.readline
f = [1, 2, 3, 5, 8, 13, 21, 34, 55, 89]
for i in range(int(input())):
    n, m = map(int, input().split())
    out = []
    for j in range(m):
        w, l, h = map(int, input().split())
        if max(w, l, h) >= f[n - 1] + f[n - 2] and min(w, l, h) >= f[n - 1]:
            out.append("1")
        else:
            out.append("0")
    print("".join(out))
