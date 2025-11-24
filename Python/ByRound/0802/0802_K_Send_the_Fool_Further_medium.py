# Problem: CF 802 K - Send the Fool Further! (medium)
# https://codeforces.com/contest/802/problem/K

"""
Algorithm: Tree Dynamic Programming with DFS
Purpose: Calculate the maximum cost of tickets Heidi might need to pay in worst-case scenario.
Time Complexity: O(n * k * log k) due to sorting operations in nlargest calls.
Space Complexity: O(n) for storing graph, parent array, and DP arrays.
"""

import sys
from heapq import nlargest
from math import inf

input = lambda: sys.stdin.readline().rstrip()
n, k = map(int, input().split())
graph = [[] for _ in range(n)]
for _ in range(n - 1):
    a, b, c = map(int, input().split())
    graph[a].append((b, c))
    graph[b].append((a, c))

# Build DFS traversal order and parent array
parent = [-1] * n
stack = [0]
dfs_order = []
while stack:
    u = stack.pop()
    dfs_order.append(u)
    for v, w in graph[u]:
        if parent[u] == v:
            continue
        parent[v] = u
        stack.append(v)

# DP arrays: f[u] represents max sum of k best paths from u, g[u] for all best paths
f = [0] * n
g = [0] * n

# Process nodes in reverse DFS order
for u in reversed(dfs_order):
    t0 = []  # Values to consider for f array (sum of edge weights in child subtrees)
    t1 = []  # Values for g array (sum of edge weights in child subtrees)
    for v, w in graph[u]:
        if parent[v] == u:
            t0.append(f[v] + w)
            t1.append(g[v] + w)

    if t0:
        # Take the k largest values from t0 to compute g[u]
        t = nlargest(k, t0)
        g[u] = sum(t)
        f[u] = g[u]
        if len(t) == k:
            f[u] -= t[-1]  # Remove last (smallest among top k) value for f computation

        to_add = -inf
        # For each child, find the best way to add one more visit
        for i in range(len(t0)):
            to_add = max(to_add, t1[i] - max(t0[i], t[-1]))

        g[u] += to_add

print(g[0])


# https://github.com/VaHiX/CodeForces/