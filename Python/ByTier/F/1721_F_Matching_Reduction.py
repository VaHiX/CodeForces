# Problem: CF 1721 F - Matching Reduction
# https://codeforces.com/contest/1721/problem/F

"""
Bipartite Matching Reduction Problem

This solution addresses a problem where we need to:
1. Maintain a maximum matching in a bipartite graph
2. For each query of type 1, remove the minimum number of vertices such that 
   the maximum matching size decreases by exactly 1
3. Return the vertices removed and the sum of edge indices in the new matching  
4. For query of type 2, return the actual edges in the maximum matching

Algorithms used:
- Hopcroft-Karp algorithm for maximum bipartite matching
- Minimum vertex cover using König's theorem
- Tracking matching edges and vertices

Time Complexity: O(m * sqrt(n)) where n = n1 + n2, m = number of edges
Space Complexity: O(n1 + n2 + m)
"""

import os
import sys

input = sys.stdin.buffer.readline


def bipartite_matching(n1, n2, x):
    # Initialize data structures for Hopcroft-Karp algorithm
    s0, n, m = [0] * (n1 + 3), n1 + n2, len(x) >> 1
    # Count degree of vertices in left part
    for i in range(0, 2 * m, 2):
        s0[x[i] + 2] += 1
    # Build prefix sum array for adjacency list
    for i in range(3, n1 + 3):
        s0[i] += s0[i - 1]
    # Initialize adjacency list
    G = [0] * m
    for i in range(0, 2 * m, 2):
        j = x[i] + 1
        G[s0[j]] = x[i ^ 1] + n1
        s0[j] += 1
    # Matching tracking arrays
    p = [0] * (n + 1)
    parent = [-1] * (n + 1)
    root = [0] * (n1 + 1)
    color, c = [0] * (n1 + 1), 1
    f = 1
    while f:
        q, f = [], 0
        # Find unmatched vertices in left part
        for i in range(1, n1 + 1):
            if not p[i]:
                parent[i], color[i] = 0, c
                root[i] = i
                q.append(i)
        for i in q:
            if p[root[i]]:
                continue
            # Try to find augmenting path
            for w in range(s0[i], s0[i + 1]):
                j = G[w]
                if not p[j]:
                    k, f = i, 1
                    # Augment path
                    while j:
                        p[j], p[k] = k, j
                        j = parent[k]
                        k = parent[j]
                    break
                k = p[j]
                if color[k] ^ c:
                    parent[j], parent[k] = i, j
                    root[k] = root[i]
                    color[k] = c
                    q.append(k)
        c += 1
    # Convert matching to proper format
    for i in range(1, n1 + 1):
        if p[i]:
            p[i] -= n1
    return p, G, s0


def f(u, v):
    # Output vertices to remove and sum of matching edges
    os.write(1, b"%d\n%d\n%d\n" % (1, u, v))
    return


def g(u):
    # Output matching edges
    os.write(1, b"%d\n%s\n" % (len(u), " ".join(map(str, u)).encode()))
    return


# Read input
n1, n2, m, q = map(int, input().split())
x = [0] * (2 * m)
for i in range(m):
    u, v = map(int, input().split())
    x[2 * i], x[2 * i + 1] = u, v

# Compute maximum matching
p, G, s0 = bipartite_matching(n1, n2, x)

# Find matching edges
y = []
s = 0
for i in range(m):
    u, v = x[2 * i], x[2 * i + 1]
    if p[u] == v:
        y.append(i + 1)
        s += i + 1

# Find minimum vertex cover using König's theorem
n = n1 + n2
visit = [0] * (n + 1)
q0 = []
# Start BFS from unmatched vertices in left part
for i in range(1, n1 + 1):
    if not p[i]:
        visit[i] = 1
        q0.append(i)
for i in q0:
    if i <= n1:
        # Follow edges to right part
        for v in range(s0[i], s0[i + 1]):
            j = G[v]
            if p[i] ^ j and not visit[j]:
                visit[j] = 1
                q0.append(j)
    else:
        # Follow back edges to left part
        j = p[i]
        if not visit[j]:
            visit[j] = 1
            q0.append(j)

# Mark vertices in minimum vertex cover
mvc = [0] * (n + 1)
for i in range(1, n1 + 1):
    if not visit[i]:
        mvc[i] = 1
for i in range(n1 + 1, n + 1):
    if visit[i]:
        mvc[i] = 1

# Process queries
for _ in range(q):
    t = int(input())
    if t == 1:
        # Remove one edge from matching
        i = y.pop()
        # Determine which vertex to remove
        u = x[2 * i - 2] if mvc[x[2 * i - 2]] else -x[2 * i - 1]
        s -= i
        f(u, s)
    else:
        # Output the matching
        g(y)


# https://github.com/VaHiX/CodeForces/