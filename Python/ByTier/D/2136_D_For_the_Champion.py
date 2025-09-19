# Contest 2136, Problem D: For the Champion
# URL: https://codeforces.com/contest/2136/problem/D

import sys, math

input = sys.stdin.readline
from collections import deque

D = ["L", "R", "U", "D"]


def go(dir, k):
    print(f"? {D[dir]} {k}")
    sys.stdout.flush()


T = int(input())
for _ in range(T):
    n = int(input())
    a = []
    b = []
    c = []
    for _ in range(n):
        x, y = map(int, input().split())
        a.append((x, y))
        b.append(x + y)
        c.append(x - y)
    c.sort()
    b.sort()
    mxb = b[-1]
    mxc = c[-1]
    # print(mxb,mxc)
    con = 4 * 10**9
    go(2, 10**9)
    input()
    go(2, 10**9)
    input()
    go(1, 10**9)
    input()
    go(1, 10**9)
    d1 = int(input())
    go(3, 10**9)
    input()
    go(3, 10**9)
    input()
    go(3, 10**9)
    input()
    go(3, 10**9)
    d2 = int(input())
    x = (mxb + mxc + d1 + d2 - 2 * con) // 2
    y = x - mxc - d2 + con
    # print(d1,d2,x,y)
    print(f"! {x} {y}")
    sys.stdout.flush()
