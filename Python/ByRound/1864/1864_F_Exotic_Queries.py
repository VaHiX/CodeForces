# Problem: CF 1864 F - Exotic Queries
# https://codeforces.com/contest/1864/problem/F

"""
Algorithm: Segment Tree + Coordinate Compression + Sweep Line
Time Complexity: O(n log n + q log n)
Space Complexity: O(n + q)

This solution uses a segment tree and coordinate compression to efficiently solve the problem of 
minimizing operations needed to reduce values in a given range to zero. The key idea is to 
process elements in order of their values and use a sweep line technique to maintain the 
minimum number of operations required.

The core technique involves:
1. Coordinate compression using segment tree
2. Sweep line algorithm for processing events
3. Fenwick tree for prefix sum queries
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def f(u, v):
    # Helper function to create a key for sorting
    return u * (n + 1) + v


def update(i, x):
    # Update segment tree at position i with value x
    i += l1
    tree[i] = x
    i >>= 1
    while i:
        tree[i] = max(tree[2 * i], tree[2 * i + 1])
        i >>= 1
    return


def get_max(s, t):
    # Get maximum value in range [s, t] from segment tree
    s, t = s + l1, t + l1
    ans = 0
    while s <= t:
        if s & 1:
            ans = max(ans, tree[s])
            s += 1
        s >>= 1
        if not t & 1:
            ans = max(ans, tree[t])
            t -= 1
        t >>= 1
    return ans


def make_graph(n, m):
    # Build a graph for sweep line using coordinate compression
    x, s = [0] * (2 * m), [0] * (n + 3)
    for i in range(0, 2 * m, 2):
        j = i >> 1
        s[l0[j] + 2] += 1
        x[i], x[i + 1] = l0[j], j
    for i in range(3, n + 3):
        s[i] += s[i - 1]
    G = [0] * m
    for i in range(0, 2 * m, 2):
        j = x[i] + 1
        G[s[j]] = x[i ^ 1]
        s[j] += 1
    return G, s


def get_sum0(i):
    # Get prefix sum up to position i using Fenwick tree
    s = 0
    while i > 0:
        s += tree[i]
        i -= i & -i
    return s


def get_sum(s, t):
    # Get range sum using Fenwick tree
    ans = 0 if s > t else get_sum0(t) - get_sum0(s - 1)
    return ans


def add(i, x):
    # Add value x to Fenwick tree at position i
    while i < len(tree):
        tree[i] += x
        i += i & -i


n, q = map(int, input().split())
a = list(map(int, input().split()))
x = [f(a[i], i) for i in range(n)]
x.sort()
l1 = pow(2, (n + 1).bit_length())
l2 = 2 * l1
tree = [0] * l2
tree0 = [0] * (n + 1)
u = []
for i in range(n - 1):
    l, r = x[i] % (n + 1), x[i + 1] % (n + 1)
    if a[l] == a[r]:
        ma = get_max(l, r)
        if ma:
            tree0[a[l]] += 1
            u.append(f(ma, a[l]))
    update(l, a[l])
tree = tree0
for i in range(1, n + 1):
    j = i + (i & -i)
    if j < len(tree):
        tree[j] += tree[i]
cnt, s = [0] * (n + 1), [0] * (n + 1)
for i in a:
    cnt[i] += 1
    s[i] = 1
for i in range(1, n + 1):
    cnt[i] += cnt[i - 1]
    s[i] += s[i - 1]
l0, r0 = [0] * q, [0] * q
for i in range(q):
    l, r = map(int, input().split())
    l0[i], r0[i] = l, r
G, s0 = make_graph(n, q)
u.sort()
j = 0
ans = [0] * q
for l in range(1, n + 1):
    for v in range(s0[l], s0[l + 1]):
        i = G[v]
        r = r0[i]
        v = s[r] - s[l - 1]
        ans0 = v + get_sum(l, r)
        ans[i] = ans0
    while j < len(u) and u[j] // (n + 1) == l:
        k = u[j] % (n + 1)
        add(k, -1)
        j += 1
sys.stdout.write("\n".join(map(str, ans)))


# https://github.com/VaHiX/CodeForces/