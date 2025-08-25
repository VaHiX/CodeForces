# Contest 2069, Problem F: Graph Inclusion
# URL: https://codeforces.com/contest/2069/problem/F

import random
import sys, os, io

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def f(u, v):
    return u << 20 ^ v


def g(u, v, w):
    return u << 40 ^ v << 20 ^ w


def get_segment(s, t):
    s, t = s ^ l1, t ^ l1
    while s <= t:
        if s & 1:
            yield s
            s += 1
        s >>= 1
        if not t & 1:
            yield t
            t -= 1
        t >>= 1


def get_root(s):
    while s ^ root[s]:
        s = root[s]
    return s


def unite(s, t):
    s, t = get_root(s), get_root(t)
    if s == t:
        return 0
    if rank[s] < rank[t]:
        s, t = t, s
    root[t], rs = s, rank[s]
    if rank[s] == rank[t]:
        rank[s] += 1
    return g(s, t, rs)


n, q = map(int, input().split())
rr = random.randint(1, 1 << 40)
da, db = dict(), dict()
qa, qb = [0] * (q << 2), [0] * (q << 1)
j = k = 0
z = f(n, n)
for i in range(q):
    t, x, y = input().rstrip().split()
    x, y = int(x), int(y)
    if x > y:
        x, y = y, x
    u = f(x, y) ^ rr
    if ord(t) & 1:
        if not u in da:
            da[u] = i
        else:
            qa[j], qa[j ^ 1], j = f(da.pop(u), i - 1), u ^ rr, j + 2
            qa[j], qa[j ^ 1], j = qa[j - 2], qa[j - 1] + z, j + 2
    else:
        if not u in db:
            db[u] = i
        else:
            qb[k], qb[k ^ 1], k = f(db.pop(u), i - 1), u ^ rr, k + 2
l1 = pow(2, (q + 1).bit_length())
l2 = 2 * l1
for i in da.keys():
    qa[j], qa[j ^ 1], j = f(da[i], l1 - 1), i ^ rr, j + 2
    qa[j], qa[j ^ 1], j = qa[j - 2], qa[j - 1] + z, j + 2
for i in db.keys():
    qb[k], qb[k ^ 1], k = f(db[i], l1 - 1), i ^ rr, k + 2
s0 = [0] * (l2 + 3)
for i in range(0, j, 2):
    l, r = qa[i] >> 20, qa[i] & 0xFFFFF
    for v in get_segment(l, r):
        s0[v + 2] += 1
for i in range(0, k, 2):
    l, r = qb[i] >> 20, qb[i] & 0xFFFFF
    for v in get_segment(l, r):
        s0[v + 2] += 1
for i in range(2, l2 + 3):
    s0[i] += s0[i - 1]
tree = [0] * s0[-1]
for i in range(0, j, 2):
    l, r = qa[i] >> 20, qa[i] & 0xFFFFF
    for v in get_segment(l, r):
        tree[s0[v + 1]] = qa[i ^ 1]
        s0[v + 1] += 1
for i in range(0, k, 2):
    l, r = qb[i] >> 20, qb[i] & 0xFFFFF
    for v in get_segment(l, r):
        tree[s0[v + 1]] = qb[i ^ 1]
        s0[v + 1] += 1
root = [i for i in range((n + 1) << 1)]
rank = [1 for _ in range((n + 1) << 1)]
ans = [-1] * q
visit, i = [0] * l2, 1
c1 = c2 = 0
for j in range(s0[1], s0[2]):
    s, t = tree[j] >> 20, tree[j] & 0xFFFFF
    tree[j] = unite(s, t)
    if not tree[j]:
        continue
    if s <= n:
        c1 += 1
    else:
        c2 += 1
while ans[-1] == -1:
    visit[i] = 1
    if i & l1 or visit[i << 1 ^ 1]:
        for j in range(s0[i + 1] - 1, s0[i] - 1, -1):
            if not tree[j]:
                continue
            s, t, rs = tree[j] >> 40, (tree[j] >> 20) & 0xFFFFF, tree[j] & 0xFFFFF
            rank[s], root[t] = rs, t
            if s <= n:
                c1 -= 1
            else:
                c2 -= 1
        i >>= 1
        continue
    i = i << 1 if not visit[i << 1] else i << 1 ^ 1
    for j in range(s0[i], s0[i + 1]):
        s, t = tree[j] >> 20, tree[j] & 0xFFFFF
        tree[j] = unite(s, t)
        if not tree[j]:
            continue
        if s <= n:
            c1 += 1
        else:
            c2 += 1
    if i & l1:
        ans[i ^ l1] = c1 - c2
sys.stdout.write("\n".join(map(str, ans)))
