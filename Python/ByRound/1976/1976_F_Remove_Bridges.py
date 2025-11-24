# Problem: CF 1976 F - Remove Bridges
# https://codeforces.com/contest/1976/problem/F

"""
Code Purpose:
This solution addresses the problem of minimizing the number of bridges in a tree after adding k edges.
The approach uses Euler tour techniques and segment trees to efficiently process the tree structure and 
determine the optimal edge additions.

Algorithms/Techniques:
1. Euler Tour Technique: To represent tree structure in linear time
2. Segment Tree with Lazy Propagation: To efficiently update and query the maximum distance in subtree
3. Greedy Approach: To determine the minimum number of bridges after adding k edges

Time Complexity: O(n log n) per test case
Space Complexity: O(n) for the graph representation and segment tree
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


def euler_tour(s):
    st = [s]
    now = list(s0)
    t1, t2 = [0] * (n + 1), [0] * (n + 1)
    dist = [inf] * (n + 1)
    parent = [0] * (n + 1)
    dist[s], t1[s], t = 0, 1, 1
    while st:
        i = st[-1]
        while now[i] ^ s0[i + 1] and t1[G[now[i]]]:
            now[i] += 1
        if now[i] ^ s0[i + 1]:
            j = G[now[i]]
            t += 1
            t1[j] = t
            dist[j] = dist[i] + 1
            parent[j] = i
            st.append(j)
        else:
            t += 1
            t2[i] = t
            st.pop()
    return t1, t2, dist, parent


def f(u, v):
    return u << 20 ^ v


def update(l, r, s):
    update0(l - 1, -s)
    update0(r, s)
    return


def update0(x, s):
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


t = int(input())
ans = []
inf = pow(10, 9) + 1
for _ in range(t):
    n = int(input())
    G, s0 = make_graph(n, n - 1)
    t1, t2, dist, parent = euler_tour(1)
    l1 = pow(2, (2 * n + 1).bit_length())
    l2 = 2 * l1
    tree, lazy = [0] * l2, [0] * l2
    for i in range(2, n + 1):
        if s0[i + 1] - s0[i] == 1:
            tree[t1[i] ^ l1] = f(dist[i], i)
    for i in range(l1 - 1, 0, -1):
        tree[i] = max(tree[i << 1], tree[i << 1 ^ 1])
    ans0, c, j = [0] * (n - 1), 0, 0
    visit = [0] * (n + 1)
    visit[1] = 1
    while tree[1] >> 20:
        i = tree[1] & 0xFFFFF
        while not visit[i]:
            visit[i] = 1
            c += 1
            l, r = t1[i], t2[i]
            update(l, r, -(1 << 20))
            i = parent[i]
        j += 1
        if j & 1:
            ans0[j >> 1] = n - c - 1
    ans.append(" ".join(map(str, ans0)))
sys.stdout.write("\n".join(ans))


# https://github.com/VaHiX/CodeForces/