# Problem: CF 1695 D1 - Tree Queries (Easy Version)
# https://codeforces.com/contest/1695/problem/D1

"""
Algorithm: Tree Diameter and Centroid Finding
This code determines the minimum number of queries required to identify a hidden vertex in a tree.
It uses the concept of tree diameter and centroid properties to compute the minimum number of queries needed.
Time Complexity: O(n) where n is the number of vertices in the tree
Space Complexity: O(n) for storing the adjacency list representation of the tree
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def make_graph(n, m):
    # Build adjacency list representation of the tree
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
    # Perform BFS from vertex s to compute distances
    q = [s]
    dist = [inf] * (n + 1)
    dist[s] = 0
    for k in range(n):
        i = q[k]
        di = dist[i]
        for v in range(s0[i], s0[i + 1]):
            j = G[v]
            if dist[j] == inf:
                q.append(j)
                dist[j] = di + 1
    return q, dist


t = int(input())
ans = []
inf = pow(10, 9) + 1
for _ in range(t):
    n = int(input())
    if n == 1:
        # If there's only one vertex, no queries are needed
        ans0 = 0
        ans.append(ans0)
        continue
    G, s0 = make_graph(n, n - 1)
    s = -1
    # Find a vertex with degree >= 3 (potential centroid)
    for i in range(1, n + 1):
        if s0[i + 1] - s0[i] >= 3:
            s = i
            break
    if s == -1:
        # If no vertex has degree >= 3, it's a path
        # We need just 1 query to distinguish between two endpoints
        ans0 = 1
        ans.append(ans0)
        continue
    # Find farthest vertices from the chosen vertex s
    p, dist = bfs(s)
    dp = [0] * (n + 1)
    # Dynamic programming to compute the minimum queries needed
    for i in p[::-1]:
        dpi, u = 0, 0
        for v in range(s0[i], s0[i + 1]):
            j = G[v]
            if dist[i] < dist[j]:
                dpi += max(dp[j], u)
                u = max(u, min(dp[j], 1) ^ 1)
        dp[i] = dpi
    # The answer is the value at the centroid vertex
    ans0 = dp[s]
    ans.append(ans0)
sys.stdout.write("\n".join(map(str, ans)))


# https://github.com/VaHiX/CodeForces/