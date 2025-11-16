# Problem: CF 1941 G - Rudolf and Subway
# https://codeforces.com/contest/1941/problem/G

"""
Algorithm: Dijkstra's shortest path with line-color compression
Approach:
1. For each color (subway line), create a virtual node that represents all stations of that line
2. Connect each real station to its corresponding virtual color node
3. Run Dijkstra from start to end using this compressed graph
4. Each edge has weight 0 (on same line) or 1 (changing lines)

Time Complexity: O((V + E) * log V) where V is number of nodes and E is edges
Space Complexity: O(V + E) for storing the graph and distances

The key insight is to treat each subway line as a single node in the graph,
so that moving from one station to another on the same line costs 0,
but moving from one line to another costs 1.
"""

import heapq
import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def make_graph(n, m):
    # Build adjacency list representation of the graph
    s = [0] * (n + 3)
    for i in x:
        s[i + 2] += 1
    for i in range(3, n + 3):
        s[i] += s[i - 1]
    G, W = [0] * (2 * m), [0] * (2 * m)
    for i in range(2 * m):
        j = x[i] + 1
        G[s[j]] = x[i ^ 1]
        W[s[j]] = i & 1
        s[j] += 1
    return G, W, s


def h(u, v):
    # Helper function to pack distance and node into a single integer for heap
    return u << 20 ^ v


def dijkstra(s, g):
    # Standard Dijkstra's algorithm for shortest path
    dist = [inf] * (n + 1)
    dist[s] = 0
    visit = [0] * (n + 1)
    p = []
    heapq.heappush(p, h(dist[s], s))
    while p:
        x = heapq.heappop(p)
        d, u = x >> 20, x & 0xFFFFF
        if dist[u] < d:
            continue
        visit[u] = 1
        for i in range(s0[u], s0[u + 1]):
            v, c = G[i], W[i]
            nd = dist[u] + c
            if not visit[v] and nd < dist[v]:
                dist[v] = nd
                heapq.heappush(p, h(dist[v], v))
    return dist[g]


t = int(input())
ans = []
l = 2 * pow(10, 5) + 5
color = [0] * (l + 1)
z = [0] * (l + 1)
inf = pow(10, 15) + 1
for t in range(1, t + 1):
    n, m = map(int, input().split())
    x = [0] * (4 * m)
    s = n + 1
    for i in range(m):
        u, v, c = map(int, input().split())
        if color[c] ^ t:  # If this color hasn't been seen in this test case
            color[c], z[c] = t, s  # Create a new virtual node for this color
            s += 1
        x[4 * i + 0], x[4 * i + 1] = u, z[c]  # Connect u to color node
        x[4 * i + 2], x[4 * i + 3] = v, z[c]  # Connect v to color node
    n = s
    G, W, s0 = make_graph(n, 2 * m)  # Build adjacency list
    b, c = map(int, input().split())
    ans0 = dijkstra(b, c)  # Run Dijkstra
    ans.append(ans0)
sys.stdout.write("\n".join(map(str, ans)))


# https://github.com/VaHiX/CodeForces/