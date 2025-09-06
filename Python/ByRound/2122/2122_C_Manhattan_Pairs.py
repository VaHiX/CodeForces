# Contest 2122, Problem C: Manhattan Pairs
# URL: https://codeforces.com/contest/2122/problem/C

import sys, math

it = iter(map(int, sys.stdin.buffer.read().split()))
t = next(it)
res = []
for _ in range(t):
    n = next(it)
    pts = [(next(it), next(it), i + 1) for i in range(n)]
    pts.sort(key=lambda p: p[0])
    m = n // 2
    l = sorted(pts[:m], key=lambda p: p[1])
    r = sorted(pts[m:], key=lambda p: p[1])
    for i in range(m):
        res.append(f"{l[i][2]} {r[m-1-i][2]}")
sys.stdout.write("\n".join(res))
