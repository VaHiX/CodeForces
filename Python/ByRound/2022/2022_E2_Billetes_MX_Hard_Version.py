# Contest 2022, Problem E2: Billetes MX (Hard Version)
# URL: https://codeforces.com/contest/2022/problem/E2

import sys, os, io
input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

def get_root(s):
    w = 0
    while s ^ root[s]:
        s, w = root[s], w ^ dist[s]
    return s, w

def unite(s, t, w):
    s, ws = get_root(s)
    t, wt = get_root(t)
    if s == t:
        return 1 if not ws ^ wt ^ w else -1
    if rank[s] < rank[t]:
        s, t = t, s
    if rank[s] == rank[t]:
        rank[s] += 1
    root[t], dist[t] = s, dist[s] ^ ws ^ wt ^ w
    return 0

t = int(input())
ans = []
mod = pow(10, 9) + 7
l = 2 * pow(10, 5) + 5
p = [1] * l
for i in range(1, l):
    p[i] = (p[i - 1] << 30) % mod
for _ in range(t):
    n, m, k, q = map(int, input().split())
    l = n + m
    root = [i for i in range(l + 1)]
    rank = [1 for _ in range(l + 1)]
    dist = [0] * (l + 1)
    ok, u = 1, l - 1
    for _ in range(k):
        r, c, v = map(int, input().split())
        if ok:
            f = unite(r, c + n, v)
            if f == -1:
                ok = 0
            u -= f ^ 1
    ans0 = [0] * (q + 1)
    if ok:
        ans0[0] = p[u]
    for i in range(1, q + 1):
        r, c, v = map(int, input().split())
        if ok:
            f = unite(r, c + n, v)
            if f == -1:
                ok = 0
            u -= f ^ 1
        if ok:
            ans0[i] = p[u]
    ans.append("\n".join(map(str, ans0)))
sys.stdout.write("\n".join(ans))