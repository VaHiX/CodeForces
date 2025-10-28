# Problem: CF 2128 F - Strict Triangle
# https://codeforces.com/contest/2128/problem/F

"""
F. Strict Triangle

Algorithms/Techniques:
- Dijkstra's algorithm for finding shortest paths.
- Two-stage shortest path computation with modified edge weights.
- Heap-based priority queue for efficient shortest path updates.

Time Complexity:
O(m * log n) per test case, where m is number of edges and n is number of nodes.

Space Complexity:
O(n + m), for storing graph edges and auxiliary arrays.
"""

import heapq

baku = []
INF = 10**18
for _ in range(int(input())):
    n, m, k = [int(t) for t in input().split()]
    k -= 1
    edges = [[] for _ in range(n)]
    for _ in range(m):
        a, b, l, r = [int(t) for t in input().split()]
        a -= 1
        b -= 1
        edges[a].append((b, l, r))
        edges[b].append((a, l, r))
    
    # First Dijkstra: Compute shortest distances from node k to all others
    dr = [INF] * n
    h = [(0, k)]
    while h:
        d, u = heapq.heappop(h)
        if dr[u] < INF:  # Skip already processed nodes
            continue
        dr[u] = d
        for v, _, r in edges[u]:
            if dr[v] < INF:  # Skip already processed nodes
                continue
            heapq.heappush(h, (d + r, v))  # Use maximum possible weight to compute shortest path

    
    # Second Dijkstra: Compute "maximum necessary" capacity for valid path from node 0 to k
    cap = [INF] * n  # cap[u] tracks the max 'negative distance' needed to get to node u
    h = [(-dr[0], 0)]  # start with negative of dist from 0 to k (since we want max)
    while h:
        c, u = heapq.heappop(h)
        if cap[u] < INF:  # Skip already processed nodes
            continue
        cap[u] = c
        for v, l, _ in edges[u]:
            if cap[v] < INF:  # Skip already processed nodes
                continue
            nc = max(-dr[v], c + l)  # Update capacity with new edge cost
            if nc < dr[v]:  # Only push if it leads to a better solution
                heapq.heappush(h, (nc, v))
    
    baku.append("YES" if cap[n - 1] < INF else "NO")  # Check if destination can be reached with valid constraints
print(*baku)


# https://github.com/VaHiX/codeForces/