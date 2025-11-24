# Problem: CF 2122 D - Traffic Lights
# https://codeforces.com/contest/2122/problem/D

"""
D. Traffic Lights

This problem involves finding the shortest path in a graph where each node has a specific rule for which edge to take next based on current time.
The algorithm uses a modified BFS approach that simulates movement through edges in a round-robin fashion.

Algorithms:
- Modified BFS with time-aware traversal
- Time-based routing: at time t, from node u, we take the (t % degree(u))-th edge in input order

Time Complexity: O(n * m) where n is number of vertices and m is number of edges
Space Complexity: O(n + m) for adjacency list and auxiliary arrays

The solution tracks:
1. Minimum total time to reach each node
2. Minimum waiting time (when moving instead of waiting)
"""

import sys

input = lambda: sys.stdin.readline().rstrip()


def solve646():
    n, m = map(int, input().split())
    adj = [[] for _ in range(n)]  # Adjacency list representation
    for _ in range(m):
        u, v = map(int, input().split())
        u, v = u - 1, v - 1  # Convert to 0-based indexing
        adj[u].append(v)
        adj[v].append(u)
    
    n2 = 2 * n + 1  # A large value to represent infinity
    d = [n2] * n      # Distance array tracking minimum time to reach each node
    fr = [1] * n      # Flag array for visited nodes in current step
    fr[0] = d[0] = 0  # Start from node 0 with distance 0
    q = [0]           # BFS queue starting at node 0
    t, mx_t = 0, n2   # Current time and minimum time to reach target

    while t + 1 < mx_t:  # Continue while we may improve the answer
        nd = [n2] * n    # New distance array for next iteration
        for u in q:      # Process all nodes from previous step
            deg = len(adj[u])  # Degree of current node
            v = adj[u][t % deg]  # Traverse to (time % degree)-th edge
            if nd[v] > d[u]:     # If we can reach v faster through u
                nd[v] = d[u]
                if fr[v]:        # Mark as unvisited for next step
                    q.append(v)
                    fr[v] = 0
                if v == n - 1:   # Update minimum time to reach destination
                    mx_t = min(mx_t, t + 1)
            if nd[u] > d[u] + 1:  # If we can reach u faster by waiting one second
                nd[u] = d[u] + 1
                if fr[u]:         # Mark as unvisited for next step
                    q.append(u)
                    fr[u] = 0
        t, d = t + 1, nd  # Increment time and swap arrays
    
    return [mx_t, d[-1]]  # Return minimal total time and waiting time


res_test = []
for _ in range(int(input())):
    res_test.append(" ".join(map(str, solve646())))
sys.stdout.write("\n".join(res_test))


# https://github.com/VaHiX/codeForces/