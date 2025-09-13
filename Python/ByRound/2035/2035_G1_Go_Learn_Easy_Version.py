# Contest 2035, Problem G1: Go Learn! (Easy Version)
# URL: https://codeforces.com/contest/2035/problem/G1

from collections import defaultdict
from math import prod

P = 998244353


def solve():
    n, m = map(int, input().split())
    a = [list(map(int, input().split())) for _ in range(m)]

    def bsearch(x):
        l, h = 1, n
        while l < h:
            m = l + h >> 1
            yield m
            if m < x:
                l = m + 1
            else:
                h = m

    a.append([0, 0])
    a.append([n + 1, n + 1])
    a.sort()
    L = [1] * len(a)
    W = [0] * len(a)
    W[0] = 1
    for i in range(1, len(a)):
        x2, k2 = a[i]
        l = 0
        for j in range(i):
            x1, k1 = a[j]
            if k1 < k2 and W[j]:
                l = max(l, L[j])
        L[i] = l + 1
        for j in range(i):
            x1, k1 = a[j]
            q = defaultdict(int)
            if k1 < k2 and L[j] == l:
                for t in bsearch(x1):
                    if x1 < t < x2:
                        q[t] += max(0, k1 - 1)
                for t in bsearch(x2):
                    if x1 < t < x2:
                        q[t] += n - k2 + 1
                z = W[j] * pow(n, x2 - x1 - len(q) - 1, P)
                for v in q.values():
                    z = z * (n - v) % P
                W[i] = (W[i] + z) % P
    print(m - L[-1] + 2, W[-1])


for _ in range(int(input())):
    solve()
