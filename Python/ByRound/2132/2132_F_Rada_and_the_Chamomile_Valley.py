# Problem: CF 2132 F - Rada and the Chamomile Valley
# https://codeforces.com/contest/2132/problem/F

"""
F. Rada and the Chamomile Valley
Purpose:
This code determines which lanes (edges) in a connected graph are "forced" — meaning that all paths from node 1 to node n must use at least one of these lanes. The algorithm identifies bridge edges and then processes queries to determine the nearest forced edge for each given node.

Algorithms/Techniques Used:
- Bridge detection using Tarjan's algorithm (DFS with discovery time and lowest reachable vertex)
- Graph traversal to find bridges
- Shortest path BFS-style algorithm to assign distances and best edge indices

Time Complexity: O(n + m + q) per test case, where n is number of nodes, m is number of edges, and q is number of queries.
Space Complexity: O(n + m) for storing the graph, discovery times, low values, parent relationships, etc.

"""

import sys
from collections import deque

input = sys.stdin.readline


def solve():
    data = sys.stdin.buffer.read().split()
    it = iter(data)
    t = int(next(it))  # Read number of test cases
    out_lines = []
    for _case in range(t):
        n = int(next(it))   # Number of houses (nodes)
        m = int(next(it))   # Number of lanes (edges)
        U = [0] * (m + 1)   # u endpoints of edges (1-indexed)
        V = [0] * (m + 1)   # v endpoints of edges (1-indexed)
        g = [[] for _ in range(n + 1)]  # Adjacency list representation
        for i in range(1, m + 1):
            u = int(next(it))   # Read edge's start node
            v = int(next(it))   # Read edge's end node
            U[i] = u
            V[i] = v
            g[u].append((v, i))   # Add edge to adjacency list (node, id)
            g[v].append((u, i))   # Bidirectional graph

        q = int(next(it))     # Number of queries
        C = [int(next(it)) for __ in range(q)]  # Query nodes

        # Tarjan’s bridge-finding algorithm initialization
        tin = [0] * (n + 1)       # Discovery time for each node
        low = [0] * (n + 1)       # Lowest reachable discovery time of node
        tout = [0] * (n + 1)      # Finish time
        parent_edge = [0] * (n + 1)  # Parent edge id for each node
        parent = [0] * (n + 1)      # Parent node in DFS tree
        is_bridge = [False] * (m + 1)  # Tracks if an edge is a bridge
        timer = 0
        start = 1     # Start vertex for DFS
        stack = []
        stack.append((start, 0))   # Stack holds (node, next neighbor index)
        parent[start] = 0
        parent_edge[start] = 0

        # Running Tarjan’s algorithm to find all bridges
        while stack:
            u, idx = stack[-1]    # Peek at top of stack
            if tin[u] == 0:       # Node not yet discovered
                timer += 1
                tin[u] = low[u] = timer

            if idx < len(g[u]):   # If there are unvisited neighbors
                v, eid = g[u][idx]    # Get node and edge id
                stack[-1] = (u, idx + 1)  # Update to next neighbor in stack
                if eid == parent_edge[u]:  # Skip parent edge (avoid backtracking)
                    continue
                if tin[v] == 0:    # If neighbor not visited yet
                    parent[v] = u              # Set parent
                    parent_edge[v] = eid       # Set parent edge id
                    stack.append((v, 0))       # Push to DFS stack
                else:
                    # Back edge found - relax lowest reachable time
                    if tin[v] < tin[u]:
                        if tin[v] < low[u]:
                            low[u] = tin[v]
            else:      # All neighbors processed for node u
                if parent[u] != 0:
                    p = parent[u]
                    pe = parent_edge[u]
                    # Check if u -- pe -- p is a bridge
                    if low[u] > tin[p]:
                        is_bridge[pe] = True
                    # Propagate lowest value up the tree
                    if low[u] < low[p]:
                        low[p] = low[u]
                tout[u] = timer
                stack.pop()

        # Function to check if x belongs to subtree rooted at rootchild
        def in_subtree(x, rootchild):
            return tin[rootchild] <= tin[x] <= tout[rootchild]

        # Identify forced edges — bridges that separate source from destination components
        forced = [False] * (m + 1)
        s = 1      # Source node
        tnode = n  # Target node
        for v in range(1, n + 1):
            eid = parent_edge[v]
            if eid == 0:
                continue
            if not is_bridge[eid]:
                continue
            # Is the edge "forced"? i.e., separates s/t from each other through this bridge
            if in_subtree(s, v) ^ in_subtree(tnode, v):
                forced[eid] = True

        # Collect all forced edges
        forced_edges = [i for i in range(1, m + 1) if forced[i]]
        if not forced_edges:
            out_lines.append(" ".join(["-1"] * q))
            continue

        # Assign shortest distances and best (smallest edge id) to each node via BFS-like traversal
        INF = 10**18
        dist = [INF] * (n + 1)
        best = [10**18] * (n + 1)
        dq = deque()
        
        # Initialize with forced edges
        for eid in forced_edges:
            a = U[eid]
            b = V[eid]
            # Update distance and best edge if current is better than previous
            if dist[a] > 0 or (dist[a] == 0 and eid < best[a]):
                dist[a] = 0
                best[a] = eid
                dq.append(a)
            if dist[b] > 0 or (dist[b] == 0 and eid < best[b]):
                dist[b] = 0
                best[b] = eid
                dq.append(b)

        # BFS-style update of distances and optimal edges
        while dq:
            u = dq.popleft()
            du = dist[u]
            bu = best[u]
            # Traverse neighbors
            for v, eid in g[u]:
                nd = du + 1   # New dist to neighbor
                # Update if better path found
                if nd < dist[v] or (nd == dist[v] and bu < best[v]):
                    dist[v] = nd
                    best[v] = bu
                    dq.append(v)

        # Process queries
        ans = []
        for c in C:
            ans.append("-1" if dist[c] >= INF else str(best[c]))
        out_lines.append(" ".join(ans))
    sys.stdout.write("\n".join(out_lines))


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/codeForces/