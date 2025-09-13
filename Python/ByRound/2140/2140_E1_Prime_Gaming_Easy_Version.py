# Contest 2140, Problem E1: Prime Gaming (Easy Version)
# URL: https://codeforces.com/contest/2140/problem/E1

import sys

input = sys.stdin.readline

for _ in range(int(input())):
    n, m = map(int, input().split())
    k, c, mod = int(input()), list(map(int, input().split())), 10**9 + 7
    if m == 1:
        print(1)
        continue
    a = [[] for _ in range(n + 1)]
    for p in range(1, n + 1):
        for x in c:
            if x <= p:
                a[p].append(x)
    q = bytearray(2)
    q[0] = 0
    q[1] = 1
    for p in range(2, n + 1):
        s = 1 << p
        u = bytearray(s)
        t = (n - p) % 2 == 0
        o = a[p]
        for S in range(s):
            if t:
                r = 0
                for i in o:
                    l = S & ((1 << (i - 1)) - 1)
                    h = S >> i
                    sh = l | (h << (i - 1))
                    if q[sh]:
                        r = 1
                        break
                u[S] = r
            else:
                r = 1
                for i in o:
                    l = S & ((1 << (i - 1)) - 1)
                    h = S >> i
                    sh = l | (h << (i - 1))
                    if not q[sh]:
                        r = 0
                        break
                u[S] = r
        q = u
    w = sum(q)
    T = pow(m, n, mod)
    z = (T - w + mod) % mod
    ans = (z + 2 * w) % mod
    print(ans)
