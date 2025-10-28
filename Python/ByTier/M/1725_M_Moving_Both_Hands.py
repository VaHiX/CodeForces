# Problem: CF 1725 M - Moving Both Hands
# https://codeforces.com/contest/1725/problem/M

"""
Algorithm: Dijkstra's shortest path with state compression
Purpose: Find minimum time to bring two hands together on a directed graph
Time Complexity: O((N + M) * log(N + M)) where N is vertices, M is edges
Space Complexity: O(N + M) for graph storage and distance array

The problem is modeled as a graph where each vertex has two states:
- One for left hand position (0 to N-1)
- One for right hand position (N to 2N-1)

We use a modified Dijkstra to find shortest paths from vertex 1 (left hand) to all other positions,
considering that both hands move independently but must meet.
"""

import sys
from heapq import heappop, heappush

RI = lambda: map(int, sys.stdin.buffer.readline().split())
print = lambda d: sys.stdout.write(str(d) + "\n")
inf = 10**16
n, m = RI()
# Build adjacency list with compressed state
# g[u] stores edges from vertex u, where each entry is (weight << 20 | destination)
g = [[u + n] if u <= n else [] for u in range(n << 1 | 1)] # Initialize graph with vertex mapping
for _ in range(m):
    u, v, w = RI()
    # Add edge from u to v with weight w
    g[u].append(w << 20 | v)
    # Add reverse edge for right hand movement (vertex v+n is the right hand state of vertex v)
    g[v + n].append(w << 20 | (u + n))

# Distance array for all states (0 to 2N-1)
dis = [inf] * (n << 1 | 1)
dis[1] = 0  # Start with left hand at vertex 1
mask = (1 << 20) - 1  # Mask to extract destination from combined value
q = [1]  # Priority queue initialized with starting vertex
while q:
    s = heappop(q)  # Get vertex with minimum distance
    c, u = s >> 20, s & mask  # Extract cost and vertex
    if c > dis[u]:  # Skip if we already found a shorter path
        continue
    for wv in g[u]:  # Iterate through adjacent vertices
        w, v = wv >> 20, wv & mask  # Extract weight and destination
        d = w + c  # New distance
        if d < dis[v]:  # Relax edge if shorter path found
            dis[v] = d
            heappush(q, d << 20 | v)  # Push updated distance to queue

# Output results for p = 2 to N (right hand at vertex 2 to N)
print(" ".join(map(lambda x: str(x) if x < inf else "-1", dis[n + 2 :])))


# https://github.com/VaHiX/CodeForces/