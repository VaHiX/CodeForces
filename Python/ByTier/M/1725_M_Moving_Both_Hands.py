# Contest 1725, Problem M: Moving Both Hands
# URL: https://codeforces.com/contest/1725/problem/M

import sys

from heapq import heappop, heappush

RI = lambda: map(int, sys.stdin.buffer.readline().split())
print = lambda d: sys.stdout.write(str(d) + "\n")

inf = 10**16

n, m = RI()
g = [[u + n] if u <= n else [] for u in range(n << 1 | 1)]
for _ in range(m):
    u, v, w = RI()
    g[u].append(w << 20 | v)
    g[v + n].append(w << 20 | (u + n))

dis = [inf] * (n << 1 | 1)
dis[1] = 0

mask = (1 << 20) - 1

q = [1]
while q:
    s = heappop(q)
    c, u = s >> 20, s & mask
    if c > dis[u]:
        continue
    for wv in g[u]:
        w, v = wv >> 20, wv & mask
        d = w + c
        if d < dis[v]:
            dis[v] = d
            heappush(q, d << 20 | v)

print(" ".join(map(lambda x: str(x) if x < inf else "-1", dis[n + 2 :])))
