# Contest 2138, Problem C2: Maple and Tree Beauty (Hard Version)
# URL: https://codeforces.com/contest/2138/problem/C2

import sys

input = lambda: sys.stdin.readline().rstrip()
ii = lambda: int(input())
mii = lambda: map(int, input().split())
lii = lambda: list(mii())

from collections import defaultdict


def solve():
    n, k = mii()
    g = [[] for _ in range(n)]
    for v, u in enumerate(mii(), 1):
        g[u - 1].append(v)
    cnt = defaultdict(int)
    cnt[1] = 1
    q = [0]
    flag = True
    while q and flag:
        tmp = []
        for u in q:
            if not g[u]:
                flag = False
                break
            tmp.extend(g[u])
        if flag:
            cnt[len(tmp)] += 1
            q = tmp
    mx = sum(cnt.values())
    tot = sum(x * c for x, c in cnt.items())
    if tot <= k or tot <= n - k:
        return mx
    f = 1
    for x, c in cnt.items():
        for b in range(c.bit_length() - 1):
            f |= f << (x << b)
        rem = c + 1 - (1 << (c.bit_length() - 1))
        if rem:
            f |= f << (x * rem)
    f &= (1 << (k + 1)) - 1
    f >>= tot - n + k
    return mx if f else mx - 1


for _ in range(ii()):
    print(solve())
