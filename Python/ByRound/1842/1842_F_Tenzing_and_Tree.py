# Problem: CF 1842 F - Tenzing and Tree
# https://codeforces.com/contest/1842/problem/F

"""
Algorithm: Tree Edge Value Maximization
Techniques: 
- Tree traversal using adjacency list representation
- Dynamic programming on tree structure
- Edge weight calculation based on component sizes

Time Complexity: O(n^2) where n is the number of vertices
Space Complexity: O(n) for storing graph and auxiliary arrays

This code computes the maximum value of a tree when exactly k vertices are painted black,
and the rest are white, for all k from 0 to n. The value of the tree is the sum of absolute
differences in black vertex counts across all edges after removal.
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


n = int(input())
G, s0 = make_graph(n, n - 1)
inf = pow(10, 9) + 1
mi = [inf] * (n + 1)  # minimum value array for dynamic programming
q = [0] * n  # queue for BFS traversal
for s in range(1, n + 1):
    if n >= 3 and s0[s + 1] - s0[s] == 1:
        continue  # skip leaf nodes in certain conditions
    q[0], l, u = s, 1, 0
    dist = [inf] * (n + 1)
    dist[s] = 0
    for i in q:
        di = dist[i]
        for v in range(s0[i], s0[i + 1]):
            j = G[v]
            if dist[j] == inf:
                q[l] = j
                dist[j] = di + 1
                u += di + 1
                mi[l + 1] = min(mi[l + 1], u)
                l += 1
ans = [(n - 1) * i - 2 * mi[i] for i in range(n + 1)]
ans[0], ans[1] = 0, n - 1  # special case for k=0 and k=1
sys.stdout.write(" ".join(map(str, ans)))


# https://github.com/VaHiX/CodeForces/