# Problem: CF 1767 E - Algebra Flash
# https://codeforces.com/contest/1767/problem/E

"""
Algebra Flash 2.2 - Colored Platforms

This solution uses a Union-Find (Disjoint Set Union) data structure to group platforms by their colors,
then applies dynamic programming with bitmasks to find the minimum cost to activate platforms such
that a path from platform 1 to platform n exists.

Time Complexity: O(n + m^2 + 2^m * m + 2^l * l) where m is the number of colors and l is the size of the largest group
Space Complexity: O(m^2 + 2^m + 2^l)

Algorithms/Techniques:
- Union-Find for grouping connected components
- Bitmask DP for selecting minimal activating cost in groups
- Graph connectivity checking via adjacency matrix represented with bitmask
"""

import io
import os

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def f(u, v):
    return u * m1 + v


def get_root(s):
    v = []
    while not s == root[s]:
        v.append(s)
        s = root[s]
    for i in v:
        root[i] = s
    return s


def unite(s, t):
    rs, rt = get_root(s), get_root(t)
    if not rs ^ rt:
        return
    if rank[s] == rank[t]:
        rank[rs] += 1
    if rank[s] >= rank[t]:
        root[rt] = rs
        size[rs] += size[rt]
    else:
        root[rs] = rt
        size[rt] += size[rs]
    return


def same(s, t):
    return True if get_root(s) == get_root(t) else False


def get_size(s):
    return size[get_root(s)]


n, m = map(int, input().split())
c = list(map(int, input().split()))
x = [0] + list(map(int, input().split()))
m1 = m + 1
m2 = (m + 1) * (m + 1)
y = [0] * m2
root = [i for i in range(m1)]
rank = [1 for _ in range(m1)]
size = [1 for _ in range(m1)]
for i in range(n - 1):
    u, v = c[i], c[i + 1]
    y[f(u, v)], y[f(v, u)] = 1, 1
    unite(u, v)
y[f(c[0], c[0])], y[f(c[-1], c[-1])] = 1, 1
r = [[] for _ in range(m1)]
for i in range(1, m1):
    r[get_root(i)].append(i)
pow2 = [1]
for _ in range(22):
    pow2.append(2 * pow2[-1])
ans = 0
inf = pow(10, 9) + 1
for r0 in r:
    if not r0:
        continue
    elif len(r0) == 1 and y[f(r0[0], r0[0])]:
        ans += x[r0[0]]
        continue
    a, b = [], []
    for i in range(len(r0)):
        if not i % 2:
            a.append(r0[i])
        else:
            b.append(r0[i])
    m = len(a)
    pm = pow2[m]
    ng = [0] * pm
    for i in range(m):
        ai, pi = a[i], pow2[i]
        for j in range(i, m):
            if y[f(ai, a[j])]:
                ng[pi | pow2[j]] = 1
    for i in range(m):
        pi = pow2[i]
        for j in range(pm):
            if not j & pi:
                ng[j ^ pi] |= ng[j]
    mi = [inf] * pm
    for i in range(pm):
        co = 0
        if ng[i]:
            continue
        for j in range(m):
            if not i & pow2[j]:
                co += x[a[j]]
        mi[i] = co
    for i in range(m):
        pi = pow2[i]
        for j in range(pm - 1, -1, -1):
            if not j & pi:
                mi[j ^ pi] = min(mi[j], mi[j ^ pi])
    l = len(b)
    pl = pow2[l]
    z = [0] * l
    for i in range(l):
        bi, zi = b[i], 0
        for j in range(m):
            if y[f(bi, a[j])]:
                zi ^= pow2[j]
        z[i] = zi
    ng = [0] * pl
    for i in range(l):
        bi, pi = b[i], pow2[i]
        for j in range(i, l):
            if y[f(bi, b[j])]:
                ng[pi | pow2[j]] = 1
    for i in range(l):
        pi = pow2[i]
        for j in range(pl):
            if not j & pi:
                ng[j ^ pi] |= ng[j]
    ans0 = inf
    pm0 = pm - 1
    pl0 = pl - 1
    for i in range(pl):
        co = 0
        if ng[i ^ pl0]:
            continue
        k = 0
        for j in range(l):
            if i & pow2[j]:
                co += x[b[j]]
            else:
                k |= z[j]
        ans0 = min(ans0, co + mi[k ^ pm0])
    ans += ans0
print(ans)


# https://github.com/VaHiX/CodeForces/