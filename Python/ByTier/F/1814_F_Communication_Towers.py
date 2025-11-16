# Problem: CF 1814 F - Communication Towers
# https://codeforces.com/contest/1814/problem/F

"""
Algorithm: Union-Find with rollback and segment tree for frequency intersection
Time Complexity: O(n log M + m α(n) + M) where M = 2*10^5
Space Complexity: O(n + m + M) 
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def f(u, v, w):
    return (u * n + v) * n + w


def get_root(s):
    while s ^ root[s]:
        s = root[s]
    return s


def unite(s, t, i):
    s, t = get_root(s), get_root(t)
    if s == t:
        return
    if rank[s] < rank[t]:
        s, t = t, s
    c1, c2, c3, c4 = s, 0, t, root[t]
    if rank[s] == rank[t]:
        rank[s] += 1
        c2 = 1
    root[t] = s
    st1.append(f(c1, c3, c4))
    st2.append(4 * i + 2 * c2 + ok[s])
    ok[s] = min(s ^ get_root(0), 1) ^ 1
    return


def same(s, t):
    return True if get_root(s) == get_root(t) else False


def undo(x, y):
    s, t0 = divmod(x, n * n)
    t, rt = divmod(t0, n)
    c, oks = divmod(y % 4, 2)
    rank[s] -= c
    root[t] = rt
    if ok[s]:
        ok[t] = 1
    else:
        ok[s] = oks
    return


n, m = map(int, input().split())
l, r = [0] * n, [0] * n
for i in range(n):
    l0, r0 = map(int, input().split())
    l[i], r[i] = l0, r0
u, v = [0] * m, [0] * m
for i in range(m):
    u0, v0 = map(int, input().split())
    u[i], v[i] = u0 - 1, v0 - 1
z = 2 * pow(10, 5) + 5
l1 = pow(2, (z + 1).bit_length())
l2 = 2 * l1
s0 = [0] * l2
for u0, v0 in zip(u, v):
    l0 = max(l[u0], l[v0]) + l1
    r0 = min(r[u0], r[v0]) + l1
    while l0 <= r0:
        if l0 & 1:
            s0[l0] += 1
            l0 += 1
        l0 >>= 1
        if not r0 & 1 and l0 <= r0:
            s0[r0] += 1
            r0 -= 1
        r0 >>= 1
for i in range(1, l2):
    s0[i] += s0[i - 1]
now = [0] + list(s0)
tree = [-1] * now[l2]
for i in range(m):
    u0, v0 = u[i], v[i]
    l0 = max(l[u0], l[v0]) + l1
    r0 = min(r[u0], r[v0]) + l1
    while l0 <= r0:
        if l0 & 1:
            tree[now[l0]] = i
            now[l0] += 1
            l0 += 1
        l0 >>= 1
        if not r0 & 1 and l0 <= r0:
            tree[now[r0]] = i
            now[r0] += 1
            r0 -= 1
        r0 >>= 1
root = [i for i in range(n + 1)]
rank = [1 for _ in range(n + 1)]
ok = [0] * (n + 1)
ok[0] = 1
s0 = [0] + s0
st1, st2 = [], []
now = 1
for i in range(s0[1], s0[2]):
    j = tree[i]
    unite(u[j], v[j], 1)
visit = [0] * l2
while now:
    if now >= l1 or visit[now << 1 ^ 1]:
        visit[now] = 1
        while st1 and st2[-1] >> 2 == now:
            undo(st1.pop(), st2.pop())
        now >>= 1
        continue
    now = now << 1 if not visit[now << 1] else now << 1 ^ 1
    for i in range(s0[now], s0[now + 1]):
        j = tree[i]
        unite(u[j], v[j], now)
ans = []
for i in range(n):
    if ok[i]:
        ans.append(i + 1)
sys.stdout.write(" ".join(map(str, ans)))


# https://github.com/VaHiX/CodeForces/