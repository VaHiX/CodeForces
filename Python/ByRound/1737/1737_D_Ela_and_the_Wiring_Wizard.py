# Problem: CF 1737 D - Ela and the Wiring Wizard
# https://codeforces.com/contest/1737/problem/D

from collections import defaultdict
from heapq import heappop, heappush


def dijkstra(graph, start):
    # Dijkstra's algorithm to find shortest distances from start node
    n = len(graph)
    dist, parents = [float("inf")] * n, [-1] * n
    dist[start] = 0
    queue = [[0, start]]
    while queue:
        path_len, v = heappop(queue)
        for w, edge_len in graph[v]:
            if dist[w] > path_len + edge_len:
                dist[w], parents[w] = path_len + edge_len, v
                heappush(queue, [path_len + edge_len, w])
    return dist, parents


for _ in range(int(input())):
    n, m = [int(i) for i in input().split()]
    g = [[] for i in range(n)]
    edge = defaultdict(lambda: float("inf"))
    # Read edges and build adjacency list
    for __ in range(m):
        u, v, w = [int(i) for i in input().split()]
        u, v = u - 1, v - 1
        g[u].append([v, 1])  # Convert to 0-indexed and use weight 1 for adjacency list
        g[v].append([u, 1])
        edge[(u, v)] = min(edge[(u, v)], w)  # Store minimum weight for each edge
        edge[(v, u)] = min(edge[(u, v)], w)

    # Run Dijkstra from source (node 0) and destination (node n-1)
    dist_1, __ = dijkstra(g, 0)
    dist_n, __ = dijkstra(g, n - 1)
    
    # Add virtual node n to graph g
    g.append([])
    # Connect virtual node to all nodes with weights = dist_1[i] + dist_n[i]
    for i in range(n):
        g[-1].append([i, dist_1[i] + dist_n[i]])

    # Run Dijkstra from virtual node (node n) to get shortest paths
    t_dist, __ = dijkstra(g, n)

    ans = float("inf")
    # For each edge in the graph, simulate rewiring and calculate minimal time
    for u, v in edge:
        w = edge[(u, v)]
        # Calculate distances considering rewiring of this edge
        # Option 1: connect u to path towards n, connect v to path towards 1
        d1 = min(dist_1[u] + dist_n[v], dist_1[v] + dist_n[u]) + 1
        # Option 2: use virtual node to connect u and v, then proceed
        d2 = min(t_dist[u], t_dist[v]) + 2
        # The cost is minimum of two options, multiplied by the wire weight
        ans = min(ans, min(d1, d2) * w)
    print(ans)


# https://github.com/VaHiX/CodeForces/