# Problem: CF 2014 E - Rendez-vous de Marian et Robin
# https://codeforces.com/contest/2014/problem/E

"""
E. Rendez-vous de Marian et Robin

Purpose:
This code finds the earliest time at which Marian (starting at vertex 1) and Robin (starting at vertex n)
can meet in a graph with horses available at certain vertices. The travel times are halved when riding a horse.
Uses a modified Dijkstra's algorithm with state tracking of (player, horse_status, current_vertex).

Algorithms/Techniques:
- Modified Dijkstra's algorithm with state space (player, horse_status, vertex)
- Heap-based priority queue for efficient shortest path exploration
- State tracking: player 0 = Marian, 1 = Robin; horse_status 0 = no horse, 1 = have horse

Time Complexity: O((V + E) * log V) where V is number of vertices and E is number of edges.
Space Complexity: O(V + E) for graph representation and visited states.

Input Format:
- t test cases
- For each case: n vertices, m edges, h horses
- h horse locations
- m edges (u, v, w)

Output:
- Earliest meeting time or -1 if impossible
"""

import heapq

for _ in range(int(input())):
    n, m, h = map(int, input().split())
    a = {int(w) - 1 for w in input().split()}  # Set of vertices with horses (0-indexed)
    assert len(a) == h
    g = [{} for _ in range(n)]  # Graph represented as adjacency list
    for _ in range(m):
        u, v, w = map(int, input().split())
        g[u - 1][v - 1] = w  # Convert to 0-indexed
        g[v - 1][u - 1] = w
    # (time, player, horse_status, vertex)
    q = [(0, 0, 1, 0), (0, 1, 1, n - 1)]  # Start positions: Marian at 0, Robin at n-1, both with horses
    d = set()  # Visited states (player, horse_status, vertex)
    r = -1  # Result: earliest meeting time
    while q:
        t, p, h_status, u = heapq.heappop(q)  # Get state with minimum time
        if (p, h_status, u) in d:  # Skip if already visited
            continue
        d.add((p, h_status, u))
        # Check if both players are at same vertex with different horse statuses (i.e., one has used horse)
        if (1 - p, 0, u) in d or (1 - p, 1, u) in d:
            r = t
            break
        if u in a:  # If current node has a horse, pick it up
            h_status = 0
        for v, w in g[u].items():  # For each neighbor
            if (p, h_status, v) not in d:  # If not visited yet
                # Travel time is halved if horse is available (2 - h_status gives 2 or 1)
                heapq.heappush(q, (t + w // (2 - h_status), p, h_status, v))
    print(r)


# https://github.com/VaHiX/codeForces/