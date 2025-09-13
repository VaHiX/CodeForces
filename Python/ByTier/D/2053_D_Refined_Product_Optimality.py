# Contest 2053, Problem D: Refined Product Optimality
# URL: https://codeforces.com/contest/2053/problem/D

import io
import os
import sys
from bisect import bisect_right
from functools import reduce

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

M = 998244353

for _ in range(int(input())):
    n, q = map(int, input().split())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))

    c = sorted(a)
    d = sorted(b)

    ans = reduce(lambda x, y: (x * y) % M, [min(c[i], d[i]) for i in range(n)], 1)
    # print(ans, end=' ')
    sys.stdout.write(str(ans) + " ")

    while q:
        o, x = map(int, input().split())
        x -= 1
        if o == 1:
            i = bisect_right(c, a[x]) - 1
            if c[i] < d[i]:
                ans = (ans * pow(c[i], -1, M) * (c[i] + 1)) % M
            c[i] += 1
            a[x] += 1
        else:
            i = bisect_right(d, b[x]) - 1
            if d[i] < c[i]:
                ans = (ans * pow(d[i], -1, M) * (d[i] + 1)) % M
            d[i] += 1
            b[x] += 1

        # print(ans, end=' ')
        sys.stdout.write(str(ans) + " ")
        q -= 1
    sys.stdout.write("\n")
