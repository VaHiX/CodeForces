# Problem: CF 1811 F - Is It Flower?
# https://codeforces.com/contest/1811/problem/F

# Flowerbox
"""
Code purpose: Determine if a given graph is a k-flower for some k.
A k-flower is a graph consisting of a simple cycle of length k, 
through each vertex of which passes its own simple cycle of length k,
and these cycles do not intersect at the vertices.

Algorithms/Techniques: Graph traversal, degree analysis, cycle detection.

Time Complexity: O(n + m) per test case, where n is the number of vertices and m is the number of edges.
Space Complexity: O(n + m) for storing the adjacency list representation of the graph.
"""

import io
import os
import sys

try:
    Z = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline
except:
    Z = lambda: sys.stdin.readline().encode()
Y = lambda: map(int, Z().split())
from collections import defaultdict as dd


def f(n, m, G):
    # For a k-flower, we need at least 9 vertices (k >= 3, and 3-regular graph with k = 3)
    # and number of edges must be exactly n + k^2
    if n < 9 or m <= n:
        return 0
    d = m - n  # This will be equal to k^2 for k-flower
    # Check if d is a perfect square and d * d == n
    if d * d != n:
        return 0
    s = []
    D = [0] * n
    for i in range(n):
        D[i] = len(G[i])
        if D[i] == 4:  # Vertices with degree 4 are part of the k-cycle
            s.append(i)
        elif D[i] != 2:  # All other vertices must have degree 2
            return 0
    # The number of vertices with degree 4 should be exactly d
    if len(s) != d:
        return 0
    v = []  # Collect neighbors of first vertex s[0] that also have degree 4
    for j in G[s[0]]:
        if D[j] == 4:
            v.append(j)
    if len(v) != 2:  # First vertex should have exactly two neighbors of degree 4
        return 0
    q = [v[0]]  # BFS to check k-cycle from one of the v[0]
    t = 0  # Counter for steps
    p = s[0]
    while q:
        w = q.pop()
        c = 0
        t += 1
        if w == v[1]:  # If reached to second neighbor of s[0]
            break
        for j in G[w]:
            if j != p and D[j] == 4:
                c += 1
                q.append(j)
        if c != 1:  # Each node in k-cycle should have exactly one neighbor in k-cycle
            return 0
        p = w
    if t != d - 1:  # The length of the k-cycle must be d
        return 0
    # Now verify that all vertices in k-cycle have a k-cycle of their own
    for i in s:
        v = []
        for j in G[i]:
            if D[j] == 2:  # Neighbors with degree 2 are part of smaller cycles
                v.append(j)
        if len(v) != 2:
            return 0
        q = [v[0]]
        t = 0
        p = i
        while q:
            w = q.pop()
            t += 1
            if D[w] != 2:  # The k-cycle structure should be preserved
                return 0
            if w == v[1]:
                break
            for j in G[w]:
                if j != p:
                    q.append(j)
            p = w
        if t != d - 1:  # The length of small cycles should also be d
            return 0
    return 1


O = []
for _ in range(*Y()):
    Z()
    n, m = Y()
    G = dd(list)
    for i in range(m):
        u, v = Y()
        u -= 1
        v -= 1
        G[u].append(v)
        G[v].append(u)
    O.append(["NO", "YES"][f(n, m, G)])
print("\n".join(O))


# https://github.com/VaHiX/CodeForces/