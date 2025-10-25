# Problem: CF 1888 E - Time Travel
# https://codeforces.com/contest/1888/problem/E

"""
Purpose: 
This code solves the problem of finding the minimum number of time travels needed to reach city n from city 1 in a time-traveling Berland, where roads change over time.

Algorithms/Techniques:
- Graph traversal using a modified BFS approach with time-aware edge processing.
- Tracking pending edges per time moment in a dictionary for efficient processing.
- Using a distance array to record the minimum time travel count to reach each city.

Time Complexity: O(m + k * t) where m is the sum of all edges across all time moments, k is the number of time travels, and t is the number of time moments.
Space Complexity: O(n + m + t) for storing the graph, distance array, and pending edges.
"""

import sys


def solve():
    data = sys.stdin.read().split()
    if not data:
        return
    it = iter(data)
    n = int(next(it))
    t_val = int(next(it))
    # Build adjacency list storing edges with their time moments
    edges_by_node = [[] for _ in range(n + 1)]
    for i in range(1, t_val + 1):
        m = int(next(it))
        for j in range(m):
            u = int(next(it))
            v = int(next(it))
            edges_by_node[u].append((v, i))
            edges_by_node[v].append((u, i))
    k = int(next(it))
    times = []
    for i in range(k):
        times.append(int(next(it)))
    INF = 10**9
    dist = [INF] * (n + 1)
    dist[1] = 1
    pending_edges = {}
    # Initial setup for BFS: add edges from city 1 to pending edges
    for edge_info in edges_by_node[1]:
        v, id0 = edge_info
        if dist[v] == INF:
            u_min = min(1, v)
            u_max = max(1, v)
            edge_rep = (u_min, u_max)
            if id0 not in pending_edges:
                pending_edges[id0] = set()
            pending_edges[id0].add(edge_rep)
    # Process each time travel according to the given sequence
    for idx in range(k):
        a_i = times[idx]
        if a_i in pending_edges:
            current_set = pending_edges[a_i]
            del pending_edges[a_i]
            for edge_rep in current_set:
                u, v = edge_rep
                # If one end is reachable, process it
                if dist[u] != INF and dist[v] == INF:
                    dist[v] = idx + 1
                    # Add edges from v to pending for next processing
                    for edge_info_v in edges_by_node[v]:
                        w, id1 = edge_info_v
                        if dist[w] == INF:
                            a1 = min(v, w)
                            b1 = max(v, w)
                            new_edge_rep = (a1, b1)
                            if id1 not in pending_edges:
                                pending_edges[id1] = set()
                            pending_edges[id1].add(new_edge_rep)
                elif dist[v] != INF and dist[u] == INF:
                    dist[u] = idx + 1
                    # Add edges from u to pending for next processing
                    for edge_info_u in edges_by_node[u]:
                        w, id1 = edge_info_u
                        if dist[w] == INF:
                            a1 = min(u, w)
                            b1 = max(u, w)
                            new_edge_rep = (a1, b1)
                            if id1 not in pending_edges:
                                pending_edges[id1] = set()
                            pending_edges[id1].add(new_edge_rep)
    if dist[n] == INF:
        print(-1)
    else:
        print(dist[n])


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/