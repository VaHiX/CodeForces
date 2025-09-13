# Contest 2066, Problem B: White Magic
# URL: https://codeforces.com/contest/2066/problem/B

import sys

input = lambda: sys.stdin.readline().rstrip()


def solve():
    n = int(input())
    a = [*map(int, input().split())]

    if a.count(0) == 0:
        print(n)
        return

    fg = 0
    b = []

    for i in a:
        if i == 0 and fg == 1:
            continue
        if i == 0:
            b.append(i)
            fg = 1
            continue
        b.append(i)

    # calc mex
    mex = [0] * (len(b) + 1)
    vis = set()
    for i in range(len(b) - 1, -1, -1):
        vis.add(b[i])
        mex[i] = mex[i + 1]
        while mex[i] in vis:
            mex[i] += 1

    fg2 = 1
    mn = b[0]
    # find mn from left and is greater than of mex
    for i in range(1, len(b)):
        if mn < mex[i]:
            fg2 = 0
        mn = min(mn, b[i])

    print(n - a.count(0) + fg2)


t = int(input())
for _ in range(t):
    solve()
