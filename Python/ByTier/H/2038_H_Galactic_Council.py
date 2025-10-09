# Problem: CF 2038 H - Galactic Council
# https://codeforces.com/contest/2038/problem/H

"""
H. Galactic Council

This problem can be solved using a Minimum Cost Maximum Flow (MCMF) approach to model
the political party dynamics over m turns.

The key idea is to:
1. Model each turn as a node in the flow network.
2. For each turn and each party, we introduce a node to represent supporting that party.
3. We use min-cost max-flow to determine how much support each party should get at each turn
   to satisfy constraints and maximize score.

Algorithms used:
- Minimum Cost Maximum Flow (MCMF)
- Bellman-Ford algorithm with queue optimization for finding shortest paths

Time Complexity: O(F * E * V) where F is the maximum flow, E is edges, V is vertices.
Space Complexity: O(V + E)

The solution constructs a graph where:
- Each turn has a corresponding node.
- Each party support choice in each turn is modeled as a node.
- Capacities and costs reflect the constraints and scoring system.

The network also ensures that in each turn, the chosen party becomes the ruling party,
and that at each time step, p[j] must be the ruling party.
"""

import sys
from collections import deque


class MCMF:
    INF = float("inf")

    class Edge:
        def __init__(self, v, c, w, r):
            self.v = v
            self.c = c
            self.w = w
            self.r = r

    def __init__(self, N):
        self.N = N
        self.gph = [[] for _ in range(N)]
        self.dist = [self.INF] * N
        self.par = [-1] * N
        self.inq = [False] * N
        self.src = 0
        self.snk = 0

    def add_edge(self, u, v, c, w):
        # Add edge from u to v with capacity c and weight w
        # Also add reverse edge with zero capacity for flow adjustments
        self.gph[u].append(self.Edge(v, c, w, len(self.gph[v])))
        self.gph[v].append(self.Edge(u, 0, -w, len(self.gph[u]) - 1))

    def shortest_path(self):
        # Bellman-Ford algorithm to find shortest path in the residual graph
        self.dist = [self.INF] * self.N
        self.par = [-1] * self.N
        self.inq = [False] * self.N
        Q = deque()
        self.dist[self.src] = 0
        self.inq[self.src] = True
        Q.append(self.src)
        while Q:
            x = Q.popleft()
            self.inq[x] = False
            for edge in self.gph[x]:
                if edge.c == 0:
                    continue
                # Relax edge (update distances and parent info)
                if self.dist[edge.v] > self.dist[x] + edge.w:
                    self.dist[edge.v] = max(self.dist[x] + edge.w, -self.INF)
                    self.par[edge.v] = edge.r
                    if not self.inq[edge.v]:
                        self.inq[edge.v] = True
                        # Insert at front of deque for better performance (SLF optimization)
                        if Q and self.dist[Q[0]] > self.dist[edge.v]:
                            Q.appendleft(edge.v)
                        else:
                            Q.append(edge.v)
        return self.dist[self.snk] != self.INF

    def flow(self, src, snk):
        # Compute minimum cost max flow from src to snk
        self.src = src
        self.snk = snk
        cost = 0
        flow = 0
        while self.shortest_path():
            val = self.INF
            x = snk
            # Find path from sink back to source and determine minimum capacity on path
            while x != src:
                edge = self.gph[x][self.par[x]]
                val = min(val, self.gph[edge.v][edge.r].c)
                x = edge.v
            x = snk
            # Adjust capacities along the path (push flow and update residual edges)
            while x != src:
                edge = self.gph[x][self.par[x]]
                self.gph[edge.v][edge.r].c -= val
                edge.c += val
                x = edge.v
            cost += self.dist[snk] * val
            flow += val
        return flow, cost


input = sys.stdin.read().split()
ptr = 0
N, M = map(int, input[ptr : ptr + 2])
ptr += 2
p = list(map(int, input[ptr : ptr + M]))
ptr += M
p = [x - 1 for x in p]
a = []
for _ in range(N):
    row = list(map(int, input[ptr : ptr + M]))
    ptr += M
    a.append(row)
b = [[0] * M for _ in range(N)]
mx_val = 1
# Precompute values for the constraint checking
for i in range(M):
    if i > 0 and p[i - 1] < p[i]:
        mx_val += 1
    for j in range(N):
        b[j][i] = mx_val - (1 if j < p[i] else 0)
mx_a = max(max(row) for row in a)
wsum = 0
S = N * M + M
E = N * M + M + 1
SP = N * M + M + 2
EP = N * M + M + 3
mcmf = MCMF(EP + 100)

# Connect source to each turn decision node (limiting support per turn)
for i in range(M):
    mcmf.add_edge(S, N * M + i, 1, 0)

# Connect each party support node to the turn nodes with appropriate cost
for i in range(M):
    for j in range(N):
        mcmf.add_edge(N * M + i, j * M + i, 1, mx_a - a[j][i])

# Build transition from support nodes to next time step or sink for final turn
for i in range(M):
    for j in range(N):
        now = j * M + i
        nxt = E if i == M - 1 else j * M + i + 1
        # Check if current position matches required party for turn i
        if j == p[i]:
            mcmf.add_edge(SP, nxt, b[j][i], 0)  # Connect start to next node (satisfy constraint)
            mcmf.add_edge(now, EP, b[j][i], 0)  # Connect current node to end (constraint satisfied)
            wsum += b[j][i]
        else:
            # For unmatched positions, continue transition
            mcmf.add_edge(now, nxt, b[j][i], 0)

# Add back edge from sink to source with infinite capacity (to allow free flow)
mcmf.add_edge(E, S, float("inf"), 0)

# First run: ensure all required constraints are met
flow1, cost1 = mcmf.flow(SP, EP)
if flow1 != wsum:
    print(-1)
    exit()

# Second run: check if each turn can be satisfied with proper support (total M supports)
flow2, cost2 = mcmf.flow(S, E)
if flow2 != M:
    print(-1)
    exit()

# Extract the solution from edges used in second flow
ans = [0] * M
for i in range(M):
    for edge in mcmf.gph[N * M + i]:
        if edge.v != S and edge.c == 0:
            ans[i] = edge.v // M
            break
print(" ".join(map(str, [x + 1 for x in ans])))


# https://github.com/VaHiX/codeForces/