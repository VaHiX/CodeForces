# Contest 2138, Problem E2: Determinant Construction (Hard Version)
# URL: https://codeforces.com/contest/2138/problem/E2

import math

maxn = 50


def attempt(x, y):
    gr = [[0] * maxn for _ in range(maxn)]
    n = maxn
    while 1:
        if x > y:
            gr[n - 1][n - 1] = 1
            gr[n - 1][n - 2] = 1
            gr[n - 2][n - 1] = -1
            x, y = y, x - y
        elif x < y:
            if y - x < x:
                gr[n - 1][n - 1] = 0
                gr[n - 1][n - 2] = 1
                gr[n - 2][n - 1] = -1
                x, y = y, x
            else:
                gr[n - 1][n - 1] = 1
                gr[n - 1][n - 2] = 1
                gr[n - 2][n - 1] = 1
                x, y = y, y - x
        elif x == 1:
            for i in range(n):
                gr[i][i] = 1
            break
        else:
            gr[n - 1][n - 1] = 1
            y = math.floor(x * ((5**0.5) - 1) / 2 + 0.5)
        if n < 2:
            return [-1]
        n -= 1
    return gr


for _ in range(int(input())):
    x = int(input())
    y = 1 if x == 1 else math.floor(x * ((5**0.5) - 1) / 2 + 0.5)
    gr = [-1]
    while len(gr) == 1:
        gr = attempt(x, y)
        y += 1
    print(maxn)
    print("\n".join([" ".join([str(j) for j in i]) for i in gr]))
