# Contest 2114, Problem D: Come a Little Closer
# URL: https://codeforces.com/contest/2114/problem/D

import sys

t = int(sys.stdin.readline())
for _ in range(int(t)):
    n = int(sys.stdin.readline())
    li = []
    xi = []
    yi = []
    for _ in range(n):
        x, y = map(int, sys.stdin.readline().split())
        li.append((x, y))
        xi.append(x)
        yi.append(y)
    xi.sort()
    yi.sort()
    if n == 1:
        print(1)
        continue
    ans = 10**20
    for x, y in li:
        xdis = xi[-1] - xi[0] + 1
        ydis = yi[-1] - yi[0] + 1
        if x == xi[0]:
            xdis -= xi[1] - xi[0]
        if x == xi[-1]:
            xdis -= xi[-1] - xi[-2]
        if y == yi[0]:
            ydis -= yi[1] - yi[0]
        if y == yi[-1]:
            ydis -= yi[-1] - yi[-2]
        if xdis * ydis == n - 1:
            ans = min(ans, min(xdis * (ydis + 1), (xdis + 1) * ydis))
        else:
            ans = min(ans, xdis * ydis)
    print(ans)
