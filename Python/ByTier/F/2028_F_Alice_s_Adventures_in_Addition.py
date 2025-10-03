# Contest 2028, Problem F: Alice's Adventures in Addition
# URL: https://codeforces.com/contest/2028/problem/F

import sys, os, io

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

from collections import deque

LOG = 14

t = int(input())
for _ in range(t):
    n, m = map(int, input().split())
    a = list(map(int, input().split()))
    prev, pfx, zero = 1, 1, 0

    mk = (1 << (m + 1)) - 1
    q = deque()

    for x in a:
        curr = zero
        if x == 0:
            curr |= pfx
            zero = curr
            q.appendleft((0, prev))
        elif x == 1:
            curr |= (prev | (prev << 1)) & mk
        else:
            prod = 1
            ptr = 0
            q.appendleft((x, prev))
            while ptr < len(q) and prod > 0 and prod * q[ptr][0] <= m:
                prod *= q[ptr][0]
                curr |= (q[ptr][1] << prod) & mk
                ptr += 1
        pfx |= curr
        prev = curr
        if len(q) > LOG:
            q.pop()

    print("YES" if (prev & (1 << m)) else "NO")
