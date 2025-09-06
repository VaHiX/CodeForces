# Contest 2097, Problem C: Bermuda Triangle
# URL: https://codeforces.com/contest/2097/problem/C

import sys, math
import heapq as hq
from itertools import permutations
from collections import Counter, defaultdict, deque
import queue

input = sys.stdin.readline

MOD = 998244353
INF = 10**9

ivar = lambda: int(input())
ivars = lambda: map(int, input().split())
ilist = lambda: list(map(int, input().split()))
istr = lambda: input().strip()


"""
        Lebron ahh freaky on my dih
"""


def solve():
    n, x, y, vx, vy = ivars()

    g = math.gcd(vx, vy)
    vx //= g
    vy //= g

    gx = math.gcd(vx, n)
    gy = math.gcd(vy, n)

    if x % gx or y % gy:
        return -1

    xc = x
    yc = y
    vxc = vx
    vyc = vy

    x //= gx
    y //= gy
    vx //= gx
    vy //= gy
    nx = n // gx
    ny = n // gy

    a = (-x) * pow(vx, -1, nx) % nx
    b = (-y) * pow(vy, -1, ny) % ny

    # print(a, b, nx, ny)

    # r * nx + a == s * ny + b (mod n)
    g = math.gcd(nx, ny)
    if a % g != b % g:
        return -1

    s = (a // g - b // g) * pow(ny // g, -1, nx // g)
    # print(s)
    t = (s * ny + b) % n
    # print(t)

    # print(xc, yc, vxc, vyc, t)

    if (xc + (t * vxc)) % n == 0 and (yc + (t * vyc)) % n == 0:
        fx, fy = (xc + (t * vxc)) // n, (yc + (t * vyc)) // n
        odd = (fx + fy) // 2
        even = abs(fx - fy) // 2
        return fx + fy + odd + even - 2
        return (fx + fy - 2) * 2
    else:
        return -1


# solve()

# for _ in range(int(input())):
#     solve()

# print(solve())

print("\n".join(map(str, (solve() for _ in range(int(input()))))))

# for _ in range(int(input())):
#     print("\n".join(solve()))
