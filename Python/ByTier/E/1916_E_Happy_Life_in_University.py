# Problem: CF 1916 E - Happy Life in University
# https://codeforces.com/contest/1916/problem/E

"""
Code Purpose:
This solution computes the maximum value of the function f(u,v) = diff(u,lca(u,v)) * diff(v,lca(u,v)) 
over all pairs of vertices u,v in a tree, where diff(u,v) is the number of distinct activities 
on the path from u to v, and lca(u,v) is the lowest common ancestor of u and v.

Approach:
1. Build the tree from parent array.
2. Use Euler Tour Technique to represent the tree as a linear structure.
3. Use a segment tree with lazy propagation to efficiently query and update the number of 
   distinct activities in subpaths.
4. For each vertex, calculate the maximum contribution from pairs (u,v) where one of them 
   is the current vertex or one of its descendants.

Time Complexity:
- Overall: O(n log n) per test case, where n is the number of vertices.
- Building the tree: O(n)
- Euler Tour: O(n)
- Segment Tree operations: O(log n) per query/update
- Total over all test cases: O(sum(n) * log(sum(n))) which is acceptable given the constraints.

Space Complexity:
- O(n) for the tree representation and auxiliary arrays.
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def make_graph(n, m):
    s = [0] * (n + 3)
    for i in range(0, 2 * m, 2):
        s[x[i] + 2] += 1
    for i in range(3, n + 3):
        s[i] += s[i - 1]
    G = [0] * m
    for i in range(0, 2 * m, 2):
        j = x[i] + 1
        G[s[j]] = x[i ^ 1]
        s[j] += 1
    return G, s


def f(u, v):
    return u << 20 ^ v


def euler_tour():
    st = [1]
    now = list(s0)
    t = 0
    t1, t2 = [-1] * (n + 1), [-1] * (n + 1)
    color, z = [0] * (n + 1), [0] * (n + 1)
    dist, cnt = [0] * (n + 1), [0] * (n + 1)
    while st:
        i = st[-1]
        j = a[i]
        if t1[i] == -1:
            t1[i] = t
            z[i] = color[j]
            color[j] = i
            dist[i] = len(st) - 1
        if now[i] == s0[i + 1]:
            t2[i] = t
            t += 1
            color[j] = z[i]
            if not color[j]:
                cnt[t1[i]] += 1
                cnt[t] -= 1
            st.pop()
        else:
            st.append(G[now[i]])
            now[i] += 1
    return t1, t2, z, dist, cnt


def update(x, s):
    p, i = l1, 1
    while x:
        lz = lazy[i]
        if not i & l1 and lz:
            lazy[i] = 0
            lazy[i << 1] += lz
            lazy[i << 1 ^ 1] += lz
        p >>= 1
        i <<= 1
        if x & p:
            lazy[i] += s
            x ^= p
            i ^= 1
    i >>= 1
    while i:
        j, k = i << 1, i << 1 ^ 1
        tree[i] = max(tree[j] + lazy[j], tree[k] + lazy[k])
        i >>= 1
    return


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


def get_max(l, r):
    ans = 0
    for i in get_segment(l, r):
        c, j = tree[i] + lazy[i], i >> 1
        while j:
            c += lazy[j]
            j >>= 1
        if ans < c:
            ans = c
    return ans


t = int(input())
ans = []
for _ in range(t):
    n = int(input())
    p = list(map(int, input().split()))
    a = [0] + list(map(int, input().split()))
    x = [0] * (2 * (n - 1))
    for i in range(n - 1):
        x[i << 1], x[i << 1 ^ 1] = p[i], i + 2
    G, s0 = make_graph(n, n - 1)
    t1, t2, z, dist, cnt = euler_tour()
    l1 = pow(2, (n + 1).bit_length())
    l2 = 2 * l1
    tree, lazy = [0] * l2, [0] * l2
    for i in range(1, n + 1):
        cnt[i] += cnt[i - 1]
    for i in range(n):
        tree[i ^ l1] = cnt[i]
    for i in range(l1 - 1, 0, -1):
        tree[i] = max(tree[i << 1], tree[i << 1 ^ 1])
    l = 0
    for i in z:
        l += min(i, 1)
    u, j = [0] * l, 0
    for i in range(1, n + 1):
        if z[i]:
            u[j] = f(z[i], i)
            j += 1
    u.sort(reverse=True)
    ans0 = tree[1]
    for i in range(1, n + 1):
        l, r = s0[i], s0[i + 1]
        if r - l >= 2:
            c, d = [0] * (r - l), dist[i]
            for v in range(l, r):
                j = G[v]
                c[l - v] = get_max(t1[j], t2[j])
            c.sort(reverse=True)
            ans0 = max(ans0, (c[0] - d) * (c[1] - d))
        while u and u[-1] >> 20 == i:
            j = u.pop() & 0xFFFFF
            update(t1[j], -1)
            update(t2[j] + 1, 1)
    ans.append(ans0)
sys.stdout.write("\n".join(map(str, ans)))


# https://github.com/VaHiX/CodeForces/