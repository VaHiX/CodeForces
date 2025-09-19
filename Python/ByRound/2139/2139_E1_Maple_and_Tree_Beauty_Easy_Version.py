# Contest 2139, Problem E1: Maple and Tree Beauty (Easy Version)
# URL: https://codeforces.com/contest/2139/problem/E1

import sys

input = lambda: sys.stdin.readline().rstrip()
ii = lambda: int(input())
mii = lambda: map(int, input().split())
lii = lambda: list(mii())


def solve():
    n, k = mii()
    g = [[] for _ in range(n)]
    for v, u in enumerate(mii(), 1):
        g[u - 1].append(v)
    layers = [1]
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
            layers.append(len(tmp))
            q = tmp
    tot = sum(layers)
    if tot <= max(k, n - k):
        return len(layers)
    dp = 1
    for x in layers:
        dp |= dp << x
    for i in range(tot + 1):
        if dp & 1:
            if i <= k and tot - i <= n - k:
                return len(layers)
        dp >>= 1
    return len(layers) - 1


for _ in range(ii()):
    print(solve())
