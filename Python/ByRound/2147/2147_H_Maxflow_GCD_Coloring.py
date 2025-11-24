# Problem: CF 2147 H - Maxflow GCD Coloring
# https://codeforces.com/contest/2147/problem/H

"""
H. Maxflow GCD Coloring

Algorithms/Techniques:
- Dinic's algorithm for computing maximum flow in a flow network
- Graph coloring based on properties of maxflows
- Gauss elimination over GF(2) for solving linear system to determine vertex partition
- Greedy coloring approach with min cut computation to assign vertices to colors

Time Complexity:
- Dinic: O(V^2 * E) per maxflow calculation, which leads to overall complexity of O(n^3 * m)
- Part function: O(n^3) using Gaussian elimination over GF(2)
- Total: O(n^4) approximately due to nested loops

Space Complexity:
- O(n^2) for adjacency lists and flow graph representation
- O(n) for auxiliary arrays like level, pointer, queue in Dinic's algorithm
"""

import math


class Dinic:
    class Edge:
        def __init__(self, to, rev, c, oc):
            # 'to' is the destination vertex
            # 'rev' is index of reverse edge in the adjacency list
            # 'c' is current capacity of the edge
            # 'oc' is original capacity of the edge
            self.to = to
            self.rev = rev
            self.c = c
            self.oc = oc

    def __init__(self, n):
        # Initialize level array for BFS in Dinic
        self.lvl = [0] * n
        # Pointer array for current edge index of each vertex in DFS
        self.ptr = [0] * n
        # Queue used in BFS to compute level of vertices
        self.q = [0] * n
        # Adjacency list to represent the graph
        self.adj = [[] for _ in range(n)]
        # Infinity value used for maxflow computation
        self.inf = 0

    def addEdge(self, a, b, c, rc=0):
        # Add forward edge from vertex 'a' to 'b'
        self.adj[a].append(self.Edge(b, len(self.adj[b]), c, c))
        # Add reverse edge from vertex 'b' to 'a'
        self.adj[b].append(self.Edge(a, len(self.adj[a]) - 1, rc, rc))
        # Update infinity value which is max of all capacities
        self.inf = max(self.inf, c, rc)

    def dfs(self, v, t, f):
        # If we reach target vertex or no flow can be pushed, return 0
        if v == t or not f:
            return f
        while self.ptr[v] < len(self.adj[v]):
            e = self.adj[v][self.ptr[v]]
            # Look for an edge that leads to a node with level exactly one higher
            if self.lvl[e.to] == self.lvl[v] + 1:
                p = self.dfs(e.to, t, min(f, e.c))
                if p:
                    # Update residual capacities and reverse edges
                    self.adj[v][self.ptr[v]].c -= p
                    self.adj[e.to][e.rev].c += p
                    return p
            self.ptr[v] += 1
        return 0

    def calc(self, s, t):
        # Compute maxflow from source 's' to sink 't'
        flow = 0
        self.q[0] = s
        self.lvl[t] = 1  # Mark target level as 1 (for BFS termination)
        while self.lvl[t]:
            # Reset level and pointer arrays for new BFS iteration
            self.lvl = [0] * len(self.q)
            self.ptr = [0] * len(self.q)
            qi = 0  # Queue start index
            qe = 1  # Queue end index
            self.lvl[s] = 1  # Mark source level as 1
            while qi < qe and not self.lvl[t]:
                v = self.q[qi]
                qi += 1
                for e in self.adj[v]:
                    # If edge not visited yet and has residual capacity, push to queue
                    if (not self.lvl[e.to]) and e.c:
                        self.q[qe] = e.to
                        self.lvl[e.to] = self.lvl[v] + 1
                        qe += 1
            p = 1
            while p:  # Continue DFS until no augmenting path found
                p = self.dfs(s, t, self.inf)
                flow += p
        return flow

    def leftMinCut(self, a):
        # Check if vertex 'a' is in the same component as source (i.e., reachable from source)
        return self.lvl[a] != 0


def part(adj):
    # Simplified Gaussian elimination over GF(2) to decompose graph into bipartite components
    n = len(adj)
    odd = -1
    for i in range(n):
        cur = 0
        for j in range(n):
            cur += adj[i][j]
        if cur & 1:
            odd = i
    if odd == -1:
        # All degrees are even, return trivial coloring
        return [0] * n
    # Adjust adjacency matrix to reduce problem dimension
    for i in range(n):
        if adj[odd][i]:
            for j in range(i + 1, n):
                if adj[odd][j]:
                    adj[i][j] ^= 1
                    adj[j][i] ^= 1
    # Create smaller matrix by removing one row/column
    adjnw = [
        [adj[i + (i >= odd)][j + (j >= odd)] for j in range(n - 1)]
        for i in range(n - 1)
    ]
    # Recursive reduction of the problem
    res = part(adjnw)
    # Insert back the removed component
    res = res[:odd] + [0] + res[odd:]
    for i in range(n):
        if adj[odd][i] and res[i] == 0:
            res[odd] ^= 1
    return res


def solve():
    n, m = map(int, input().split())
    u, v, w = [[0] * m for _ in range(3)]
    for i in range(m):
        u[i], v[i], w[i] = map(int, input().split())
        u[i] -= 1
        v[i] -= 1
    par = [0] * n
    g = 0
    for i in range(1, n):
        # Build maxflow network with all edges having edge capacities as weights
        d = Dinic(n)
        for j in range(m):
            d.addEdge(u[j], v[j], w[j], w[j])
        g = math.gcd(d.calc(i, par[i]), g)
        for j in range(i + 1, n):
            if par[j] == par[i] and d.leftMinCut(j):
                # Assign same parent to group connected vertices together
                par[j] = i
    if g != 1:
        print(1)
        print(n)
        print(" ".join(map(str, range(1, n + 1))))
        return
    print(2)
    adj = [[0] * n for _ in range(n)]
    # Process edges with odd weights to determine coloring
    for i in range(m):
        if w[i] & 1:
            adj[u[i]][v[i]] ^= 1
            adj[v[i]][u[i]] ^= 1
    ans = part(adj)
    print(sum(ans))
    print(" ".join([str(i + 1) for i in range(n) if ans[i]]))
    print(n - sum(ans))
    print(" ".join([str(i + 1) for i in range(n) if not ans[i]]))


for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/CodeForces/