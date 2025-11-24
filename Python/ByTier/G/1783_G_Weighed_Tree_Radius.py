# Problem: CF 1783 G - Weighed Tree Radius
# https://codeforces.com/contest/1783/problem/G

"""
Problem: G. Weighed Tree Radius
Purpose: Calculate the radius of a weighted tree after each vertex weight update.
Algorithm: 
    - Use Euler Tour Technique to preprocess the tree for LCA queries
    - Use Segment Tree for efficient range minimum queries
    - Use Dynamic Programming with Segment Trees to track changes in eccentricity
    - For each query, update vertex weight and recompute the radius efficiently

Time Complexity: O(n log n + m log n) where n is number of vertices and m is number of queries
Space Complexity: O(n log n) for segment trees and auxiliary data structures

The solution uses:
1. Euler Tour for LCA computation in O(1) after preprocessing
2. Segment trees for efficient range minimum queries
3. Dynamic programming with tracking of maximum eccentricity for each node
4. Efficient vertex weight updates and radius recomputation
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def make_graph(n, m):
    x, s = [0] * (2 * m), [0] * (n + 3)
    for i in range(0, 2 * m, 2):
        u, v = map(int, input().split())
        s[u + 2] += 1
        s[v + 2] += 1
        x[i], x[i + 1] = u, v
    for i in range(3, n + 3):
        s[i] += s[i - 1]
    G = [0] * (2 * m)
    for i in range(2 * m):
        j = x[i] + 1
        G[s[j]] = x[i ^ 1]
        s[j] += 1
    return G, s


def euler_tour():
    st = [1]
    dist = [inf] * (n + 1)
    t1, t2 = [-1] * (n + 1), [-1] * (n + 1)
    now = list(s0)
    v = []
    while st:
        i = st[-1]
        v.append(len(st) - 1)
        if t1[i] == -1:
            dist[i] = len(st) - 1
            t1[i] = len(v) - 1
        while now[i] ^ s0[i + 1] and dist[G[now[i]]] ^ inf:
            now[i] += 1
        if now[i] ^ s0[i + 1]:
            st.append(G[now[i]])
        else:
            t2[st.pop()] = len(v) - 1
    return t1, t2, dist, v


def f(u, v):
    return u * n0 + v


def g(u, v):
    return u << 20 ^ v


def h(u, v, w):
    return u << 40 ^ v << 20 ^ w


def get_min(l, r):
    if not l <= r:
        return 0
    d = (r - l + 1).bit_length() - 1
    ll, rr = f(d, l), f(d, r - pow2[d] + 1)
    ans = min(mi[ll], mi[rr])
    return ans


def get_segment(s, t):
    s, t = s + l1, t + l1
    ans = []
    while s <= t:
        if s & 1:
            ans.append(s)
            s += 1
        s >>= 1
        if not t & 1:
            ans.append(t)
            t -= 1
        t >>= 1
    return ans


def get_dist(u, v):
    l, r = min(t1[u], t1[v]), max(t2[u], t2[v])
    ans = dist[u] + dist[v] - 2 * get_min(l, r)
    return ans


n = int(input())
a = [0] + list(map(int, input().split()))
G, s0 = make_graph(n, n - 1)
inf = pow(10, 9) + 1
t1, t2, dist, v = euler_tour()
dist[0] = 0
pow2 = [1]
for _ in range(20):
    pow2.append(2 * pow2[-1])
n0 = len(v)
mi = [inf] * (20 * n0)
for i in range(n0):
    mi[i] = v[i]
m = n0
for i in range(1, 20):
    p = pow2[i - 1]
    m -= p
    for j in range(f(i, 0), f(i, m)):
        mi[j] = min(mi[j - n0], mi[j - n0 + p])
m = int(input())
l1 = pow(2, (m + 1).bit_length())
l2 = 2 * l1
la = [0] * (n + 1)
v0, x0 = [0] * m, [0] * m
s0 = [0] * (l2 + 3)
for i in range(m):
    v, x = map(int, input().split())
    v0[i], x0[i] = v, x
    s = get_segment(la[v], i)
    for j in s:
        s0[j + 2] += 1
    la[v] = i + 1
for i in range(1, n + 1):
    s = get_segment(la[i], l1 - 1)
    for j in s:
        s0[j + 2] += 1
for i in range(1, l2 + 3):
    s0[i] += s0[i - 1]
tree = [0] * s0[-1]
la = [0] * (n + 1)
for i in range(m):
    v, x = v0[i], x0[i]
    s = get_segment(la[v], i)
    for j in s:
        tree[s0[j + 1]] = g(a[v], v)
        s0[j + 1] += 1
    la[v], a[v] = i + 1, x
for i in range(1, n + 1):
    s = get_segment(la[i], l1 - 1)
    for j in s:
        tree[s0[j + 1]] = g(a[i], i)
        s0[j + 1] += 1
x, y, ma = 0, 0, 0
a = [0] * (n + 1)
for i in range(s0[1], s0[2]):
    aj, j = tree[i] >> 20, tree[i] & 0xFFFFF
    a[j] = aj
    u = [2 * aj, a[x] + aj + get_dist(x, j), a[y] + aj + get_dist(y, j)]
    ma0 = max(u)
    if ma < ma0:
        if u[0] == ma0:
            x, y = j, j
        elif u[1] == ma0:
            y = j
        else:
            x = j
        ma = ma0
st = [1]
now = [h(ma, x, y)]
visit = [0] * l2
visit[1] = 1
ans = []
while len(ans) ^ m:
    i = st[-1]
    if i & l1 or (visit[2 * i] and visit[2 * i + 1]):
        if i > l1:
            d = now[-1] >> 40
            ans0 = (d + 1) >> 1
            ans.append(ans0)
        for j in range(s0[i], s0[i + 1]):
            a[tree[j] & 0xFFFFF] = 0
        st.pop()
        now.pop()
        continue
    k = 2 * i if not visit[2 * i] else 2 * i + 1
    ma, xy = now[-1] >> 40, now[-1] & 0xFFFFFFFFFF
    x, y = xy >> 20, xy & 0xFFFFF
    for i in range(s0[k], s0[k + 1]):
        aj, j = tree[i] >> 20, tree[i] & 0xFFFFF
        a[j] = aj
        u = [2 * aj, a[x] + aj + get_dist(x, j), a[y] + aj + get_dist(y, j)]
        ma0 = max(u)
        if ma < ma0:
            if u[0] == ma0:
                x, y = j, j
            elif u[1] == ma0:
                y = j
            else:
                x = j
            ma = ma0
    visit[k] = 1
    st.append(k)
    now.append(h(ma, x, y))
sys.stdout.write("\n".join(map(str, ans)))


# https://github.com/VaHiX/CodeForces/