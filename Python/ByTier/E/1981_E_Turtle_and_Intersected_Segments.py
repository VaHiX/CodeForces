# Problem: CF 1981 E - Turtle and Intersected Segments
# https://codeforces.com/contest/1981/problem/E

"""
Algorithm: Union-Find with Segment Tree for Minimum Spanning Tree
Time Complexity: O(n log n)
Space Complexity: O(n)
This solution uses a segment tree to efficiently manage intervals and a union-find structure
to build the minimum spanning tree. The key idea is to sort segments by their 'a' values
and use the segment tree to track which intervals intersect with the current one.
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def f(u, v):
    # Helper function to encode two values into one
    return u << 20 ^ v


def update(i, x, y):
    # Update segment tree at position i with min x and max y
    i ^= l1
    mi[i], ma[i] = x, y
    i >>= 1
    while i:
        mi[i] = min(mi[i << 1], mi[i << 1 ^ 1])
        ma[i] = max(ma[i << 1], ma[i << 1 ^ 1])
        i >>= 1
    return


def get_min(s, t):
    # Get minimum value in range [s,t] from segment tree
    s, t = s ^ l1, t ^ l1
    ans = inf
    while s <= t:
        if s & 1:
            ans = min(ans, mi[s])
            s += 1
        s >>= 1
        if not t & 1:
            ans = min(ans, mi[t])
            t -= 1
        t >>= 1
    return ans


def get_max(s, t):
    # Get maximum value in range [s,t] from segment tree
    s, t = s ^ l1, t ^ l1
    ans = -inf
    while s <= t:
        if s & 1:
            ans = max(ans, ma[s])
            s += 1
        s >>= 1
        if not t & 1:
            ans = max(ans, ma[t])
            t -= 1
        t >>= 1
    return ans


def get_root(s):
    # Find root of s in union-find structure
    while s ^ root[s]:
        s = root[s]
    return s


def unite(s, t):
    # Union two sets in union-find structure
    s, t = get_root(s), get_root(t)
    if s == t:
        return
    if rank[s] < rank[t]:
        s, t = t, s
    if rank[s] == rank[t]:
        rank[s] += 1
    root[t] = s
    return


def same(s, t):
    # Check if two elements are in same set
    return True if get_root(s) == get_root(t) else False


t = int(input())
ans = []
inf = pow(10, 9) + 1
for _ in range(t):
    n = int(input())
    l, r, a = [0] * n, [0] * n, [0] * n
    for i in range(n):
        l0, r0, a0 = map(int, input().split())
        l[i], r[i], a[i] = l0, r0, f(a0, i)
    u, c = [0] * (n << 1), 0
    a.sort()
    for i in range(n):
        j, a[i] = a[i] & 0xFFFFF, a[i] >> 20
        u[j << 1], u[j << 1 ^ 1] = f(l[j] << 1, i), f(r[j] << 1 ^ 1, i)
    l1 = pow(2, (n + 1).bit_length())
    l2 = 2 * l1
    mi, ma = [inf] * l2, [-inf] * l2
    x, y, c = [0] * (n << 1), [0] * (n << 1), 0
    for i in sorted(u):
        j = i & 0xFFFFF
        if mi[j ^ l1] == inf:
            l, r = get_max(0, j), get_min(j, l1 - 1)
            if l ^ -inf:
                x[c], y[c], c = f(l, j), f(a[j] - a[l], c), c + 1
            if r ^ inf:
                x[c], y[c], c = f(j, r), f(a[r] - a[j], c), c + 1
            update(j, j, j)
        else:
            update(j, inf, -inf)
    root = [i for i in range(n)]
    rank = [1 for _ in range(n)]
    ans0, cnt = 0, 0
    for i in sorted(y[:c]):
        j = i & 0xFFFFF
        l, r = x[j] >> 20, x[j] & 0xFFFFF
        if not same(l, r):
            unite(l, r)
            ans0 += i >> 20
            cnt += 1
        if cnt == n - 1:
            break
    if cnt ^ (n - 1):
        ans0 = -1
    ans.append(ans0)
sys.stdout.write("\n".join(map(str, ans)))


# https://github.com/VaHiX/CodeForces/