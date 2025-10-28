# Problem: CF 2047 F - For the Emperor!
# https://codeforces.com/contest/2047/problem/F

"""
Algorithm: Minimum Cost Maximum Flow with SCC Reduction
Purpose: Find minimum number of plans to distribute to messengers so all cities are informed.
Approach:
1. Find Strongly Connected Components (SCC) to reduce graph to DAG.
2. Model the problem as a min-cost max-flow network where:
   - Each SCC is a node in the flow graph.
   - Flow represents messengers.
   - Costs represent number of plans needed.
3. Use min-cost max-flow algorithm (implemented via Bellman-Ford) to find the minimum cost to send at least one messenger per SCC.
Time Complexity: O((V + E)^2 * F) where F is the maximum flow, approximately O(n^4) in worst case.
Space Complexity: O(V + E) for storing graph and flow network.
"""

import sys
from collections import deque


class MCMF:
    def __init__(self, n):
        self.N = n  # Number of nodes
        self.S = 0  # Source node
        self.T = 0  # Sink node
        self.edges = []  # Store edges in format [u, v, capacity, cost]
        self.graph = [[] for _ in range(n)]  # Adjacency list of edges for each node

    def add_edge(self, u, v, w, cost):
        # Add forward edge and backward edge for residual graph
        self.edges.append([u, v, w, cost])
        self.edges.append([v, u, 0, -cost])  # Reverse edge has 0 capacity and negative cost
        self.graph[u].append(len(self.edges) - 2)  # Index of forward edge
        self.graph[v].append(len(self.edges) - 1)  # Index of backward edge

    def mincost_maxflow(self):
        flow, cost = 0, 0  # Total flow and cost
        INF = 10**9  # Infinity
        while True:
            dist = [INF] * self.N  # Distance from source to each node
            prev = [-1] * self.N  # Previous node in shortest path
            in_queue = [False] * self.N  # Whether node is in queue
            dist[self.S] = 0
            queue = deque([self.S])
            in_queue[self.S] = True
            while queue:
                u = queue.popleft()
                in_queue[u] = False
                for idx in self.graph[u]:
                    v, cap, cst = (
                        self.edges[idx][1],  # Destination node
                        self.edges[idx][2],  # Capacity
                        self.edges[idx][3],  # Cost
                    )
                    # Apply relax operation if edge is feasible and shorter path found
                    if cap > 0 and dist[v] > dist[u] + cst:
                        dist[v] = dist[u] + cst
                        prev[v] = idx
                        if not in_queue[v]:
                            queue.append(v)
                            in_queue[v] = True
            if dist[self.T] == INF:  # No augmenting path found
                break
            inc = INF  # Amount of flow that can be pushed
            v = self.T
            # Backtrace to find the minimum capacity on the path
            while v != self.S:
                e = prev[v]
                inc = min(inc, self.edges[e][2])
                v = self.edges[e][0]

            flow += inc  # Add flow to total
            cost += inc * dist[self.T]  # Add cost to total
            v = self.T
            # Update residual capacities
            while v != self.S:
                e = prev[v]
                self.edges[e][2] -= inc        # Reduce forward edge capacity
                self.edges[e ^ 1][2] += inc    # Increase backward edge capacity
                v = self.edges[e][0]
        return flow, cost


def scc(n, adj):
    # Kosaraju's algorithm for finding SCCs
    order = []
    visited = [False] * n
    component = [-1] * n

    def dfs1(v):
        # First DFS to get finishing order
        visited[v] = True
        for u in adj[v]:
            if not visited[u]:
                dfs1(u)
        order.append(v)

    def dfs2(v, mark):
        # Second DFS on transpose graph to assign component
        component[v] = mark
        for u in rev_adj[v]:
            if component[u] == -1:
                dfs2(u, mark)

    for v in range(n):
        if not visited[v]:
            dfs1(v)
    
    # Build reverse adjacency list
    rev_adj = [[] for _ in range(n)]
    for v in range(n):
        for u in adj[v]:
            rev_adj[u].append(v)
    
    mark = 0
    while order:
        v = order.pop()
        if component[v] == -1:
            dfs2(v, mark)
            mark += 1
    
    return mark, component  # Number of components, component assignments


def solve():
    n, m = map(int, sys.stdin.readline().split())
    a = list(map(int, sys.stdin.readline().split()))
    adj = [[] for _ in range(n)]
    
    # Read edges
    for _ in range(m):
        u, v = map(int, sys.stdin.readline().split())
        adj[u - 1].append(v - 1)  # Convert to 0-based indexing
    
    # Find SCCs
    cn, vis = scc(n, adj)
    
    # Aggregate number of messengers in each component
    sa = [0] * (cn + 1)
    g = [[] for _ in range(cn + 1)]
    for i in range(n):
        sa[vis[i] + 1] += a[i]  # Sum up messengers in each component
        for v in adj[i]:
            if vis[i] != vis[v]:
                g[vis[i] + 1].append(vis[v] + 1)  # Build component graph
    
    # Set up network for min-cost max-flow
    S = 3 * cn + 5  # Super source
    T = S + 1        # Super sink
    my = MCMF(T + 2)  # Create MCMF object
    my.S, my.T = S, T

    # Add edges in the flow network
    for i in range(1, cn + 1):
        # From super source to component i
        my.add_edge(S, i + cn, sa[i], 0)
        # From component i to its copy in middle layer
        my.add_edge(i, i + cn, 1, -1)
        # From component copy in last layer to super sink
        my.add_edge(i + 2 * cn, T, 10**9, 0)
        # Cost to move from middle to last layer (to count number of plans)
        my.add_edge(i + cn, i + 2 * cn, 1, -100000)
        # Add unbounded forward edges in last layer to ensure we can propagate
        my.add_edge(i + cn, i + 2 * cn, 10**9, 0)
    
    for u in range(1, cn + 1):
        for v in g[u]:
            # Connect between components (transitions in original graph)
            my.add_edge(u + 2 * cn, v + cn, 10**9, 0)
            my.add_edge(u + 2 * cn, v, 10**9, 0)

    # Run min-cost max-flow algorithm
    cost = my.mincost_maxflow()[1]
    
    # Adjust the result to get actual number of plans
    if cost <= -100000 * cn:
        print(cost + 100000 * cn + cn)
    else:
        print(-1)  # Impossible to inform all cities


def main():
    sys.setrecursionlimit(10**6)
    t = int(sys.stdin.readline().strip())
    for _ in range(t):
        solve()


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/