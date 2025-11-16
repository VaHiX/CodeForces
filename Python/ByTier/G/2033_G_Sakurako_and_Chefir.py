# Problem: CF 2033 G - Sakurako and Chefir
# https://codeforces.com/contest/2033/problem/G

"""
Algorithm: Tree Diameter with Staminas
This solution efficiently computes the maximum distance Chefir can travel from a given vertex
with a given stamina in a tree. It uses tree preprocessing techniques including:
- BFS to compute distances and parents
- Dynamic Programming with Binary Lifting for fast ancestor queries
- Tree diameter computation with stamina constraints

Time Complexity: O(n log n + q log n)
Space Complexity: O(n log n)

Key techniques used:
1. Binary lifting for ancestor queries
2. Tree diameter computation with stamina constraints
3. Dynamic programming on tree with stamina limits
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def make_graph(n, m):
    # Build adjacency list representation for the tree
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


def bfs(s):
    # BFS traversal to compute distances and parent relationships
    q = [s]
    dist = [inf] * (n + 1)
    dist[s] = 0
    parent = [0] * (n + 1)
    for i in q:
        di = dist[i]
        for v in range(s0[i], s0[i + 1]):
            j = G[v]
            if dist[j] == inf:
                q.append(j)
                dist[j] = di + 1
                parent[j] = i
    return q, dist, parent


def f(u, v):
    # Helper function for indexing in DP arrays
    return u * (n + 1) + v


t = int(input())
ans = []
inf = pow(10, 9) + 1
pow2 = [1]
for _ in range(20):
    pow2.append(2 * pow2[-1])
for _ in range(t):
    n = int(input())
    G, s0 = make_graph(n, n - 1)  # Build graph
    p, dist, parent = bfs(1)  # BFS to get distances and parent info
    dp1 = list(dist)  # Copy distances
    # Process nodes in reverse BFS order to compute subtree max distances
    for i in p[::-1][:-1]:
        j = parent[i]
        dp1[j] = max(dp1[j], dp1[i])
    # Compute maximum distances for each node
    ma = [0] * (n + 1)
    for i in range(1, n + 1):
        ma0, di = 0, dist[i]
        for v in range(s0[i], s0[i + 1]):
            j = G[v]
            if parent[i] == j:
                continue
            ma[j] = ma0
            ma0 = max(ma0, dp1[j] - di)
        ma0 = 0
        for v in range(s0[i + 1] - 1, s0[i] - 1, -1):
            j = G[v]
            if parent[i] == j:
                continue
            ma[j] = max(ma[j], ma0)
            ma0 = max(ma0, dp1[j] - di)
    # Binary lifting initialization for ancestor queries
    dp = [0] * (20 * (n + 1))
    dp0 = [0] * (20 * (n + 1))
    for i in range(1, n + 1):
        dp[i], dp0[i] = ma[i], parent[i]
    for i in range(1, 20):
        p = pow2[i - 1]
        for j in range(1, n + 1):
            k = dp0[f(i - 1, j)]
            if k:
                dp[f(i, j)] = max(dp[f(i - 1, j)], dp[f(i - 1, k)] + p)
                dp0[f(i, j)] = dp0[f(i - 1, k)]
    # Process queries
    q = int(input())
    ans0 = []
    for _ in range(q):
        v, k = map(int, input().split())
        k = min(k, dist[v])  # Limit stamina to depth from root
        ans1, p, i, c = dp1[v] - dist[v], 1, 0, 1
        # Use binary search approach to find maximum distance
        while k:
            if k & p:
                ans1 = max(ans1, dp[f(i, v)] + c)
                v, k, c = dp0[f(i, v)], k ^ p, c + p
            p, i = p << 1, i + 1
        ans0.append(ans1)
    ans.append(" ".join(map(str, ans0)))
sys.stdout.write("\n".join(ans))


# https://github.com/VaHiX/CodeForces/