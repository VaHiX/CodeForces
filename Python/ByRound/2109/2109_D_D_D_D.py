# Contest 2109, Problem D: D/D/D
# URL: https://codeforces.com/contest/2109/problem/D

import sys

input = lambda: sys.stdin.readline().rstrip()
ii = lambda: int(input())
mii = lambda: map(int, input().split())
lii = lambda: list(mii())

from collections import deque

inf = 10**18


def solve():
    n, m, l = mii()
    arr = lii()
    tot = sum(arr)
    mxeven, mxodd = 0, -1
    mnodd = min((x for x in arr if x & 1), default=-1)
    if tot % 2 == 0:
        mxeven = tot
        if mnodd > 0:
            mxodd = tot - mnodd
    else:
        mxodd = tot
        if mnodd > 0:
            mxeven = tot - mnodd

    g = [[] for _ in range(n)]
    for _ in range(m):
        u, v = mii()
        u -= 1
        v -= 1
        g[u].append(v)
        g[v].append(u)
    dis = [[inf] * n for _ in range(2)]
    dis[0][0] = 0
    dq = deque([(0, 0)])
    while dq:
        d, u = dq.popleft()
        for v in g[u]:
            if d + 1 < dis[d & 1 ^ 1][v]:
                dis[d & 1 ^ 1][v] = d + 1
                dq.append((d + 1, v))

    ans = [0] * n
    for u in range(n):
        if mxeven >= dis[0][u] or mxodd >= dis[1][u]:
            ans[u] = 1
    return "".join(map(str, ans))


for _ in range(ii()):
    print(solve())
