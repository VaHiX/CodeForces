# Problem: CF 1766 F - MCF
# https://codeforces.com/contest/1766/problem/F

"""
Minimum Cost Flow with Odd/Even Constraints
Algorithm: Min Cost Flow with modified edge costs and odd/even constraints
Time Complexity: O(V^2 * E * log V) where V is vertices and E is edges
Space Complexity: O(V + E)

The problem is a variant of minimum cost flow where each edge has a constraint that
its flow must be odd if capacity is odd, or even if capacity is even.
We transform the problem by:
1. Adding a dummy source and sink
2. Handling odd/even flow constraints via a transformation
3. Using min cost flow algorithm with modified costs
"""

import heapq
import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def add_edge(u, v, cost, f, e):
    # Add edge to adjacency list with cost, flow capacity, and edge index
    G[u].append([v, cost, f, len(R[v]), e])
    R[v].append([u, -cost, 0, len(G[u]) - 1, e])


def dijkstra(s):
    # Dijkstra's algorithm for finding shortest paths with potential
    dist = [inf] * l
    dist[s] = 0
    parent = [-1] * l
    p = []
    heapq.heappush(p, (0, s))
    while p:
        d, i = heapq.heappop(p)
        if dist[i] < d:
            continue
        di = dist[i] + h[i]
        for j, c, f, _, _ in G[i]:
            if not f:
                continue
            nd = di + c - h[j]
            if dist[j] > nd:
                parent[j] = i
                dist[j] = nd
                heapq.heappush(p, (nd, j))
        for j, c, f, _, _ in R[i]:
            if not f:
                continue
            nd = di + c - h[j]
            if dist[j] > nd:
                parent[j] = i
                dist[j] = nd
                heapq.heappush(p, (nd, j))
    return dist, parent


def min_cost_flow(s, t, f):
    # Find minimum cost flow using successive shortest paths
    ans = 0
    while f:
        dist, parent = dijkstra(s)
        for i in range(l):
            h[i] += dist[i]
        if not parent[t] ^ -1:
            return inf
        ma = f
        u = t
        x, y = [], []
        while u ^ s:
            v = parent[u]
            Gv = G[v]
            v0, i0, c0, mi = -1, -1, -1, inf
            for i in range(len(Gv)):
                if Gv[i][0] == u and Gv[i][2]:
                    if mi > Gv[i][1]:
                        mi = Gv[i][1]
                        v0, i0, c0 = v, i, 0
            Rv = R[v]
            for i in range(len(Rv)):
                if Rv[i][0] == u and Rv[i][2]:
                    if mi > Rv[i][1]:
                        mi = Rv[i][1]
                        v0, i0, c0 = v, i, 1
            if c0 == 0:
                ma = min(ma, Gv[i0][2])
                x.append((v0, i0))
            elif c0 == 1:
                ma = min(ma, Rv[i0][2])
                y.append((v0, i0))
            u = v
        f -= ma
        for i, j in x:
            Gi = G[i]
            Gi[j][2] -= ma
            R[Gi[j][0]][Gi[j][3]][2] += ma
        for i, j in y:
            Ri = R[i]
            Ri[j][2] -= ma
            G[Ri[j][0]][Ri[j][3]][2] += ma
        ans += h[t] * ma
    return ans


# Read input
n, m = map(int, input().split())
x0, y0, c0 = [0] * m, [0] * m, [0] * m
u = [0] * (n + 1)
l = n + 3  # extended size for source and sink
s, t = l - 2, l - 1
G = [[] for _ in range(l)]
R = [[] for _ in range(l)]
inf = 1 << 50
z = 1 << 30

# Process edges with modified capacity and cost
for i in range(m):
    x, y, c, w = map(int, input().split())
    x0[i], y0[i], c0[i] = x, y, c & 1  # store if capacity is odd
    add_edge(x, y, w << 1, c >> 1, i)  # add edge with modified capacity and cost
    if c & 1:  # if capacity is odd, modify flow constraints
        u[x] -= 1
        u[y] += 1

# Check compatibility of odd/even constraints
ok = 1
if u[1] & 1:  # if source has odd excess
    u[1] -= 1
    u[n] += 1
v = 0
for i in range(1, n + 1):
    f = abs(u[i]) >> 1  # half the absolute value of excess
    if u[i] & 1:  # if excess is odd, impossible
        ok = 0
    elif u[i] > 0:  # if excess is positive, connect to source
        add_edge(s, i, -z, f, -1)
    elif u[i] < 0:  # if excess is negative, connect to sink
        add_edge(i, t, -z, f, -1)
    v += f

# Add artificial edges for the flow constraint
add_edge(s, 1, 0, inf, -1)
add_edge(n, t, 0, inf, -1)

if ok:
    h = [inf] * l
    h[s] = 0
    f = 1
    while f:
        f = 0
        for i in range(l):
            hi = h[i]
            for j, c, f0, _, _ in G[i]:
                if f0 and h[j] > hi + c:
                    h[j], f = hi + c, 1
    f, f0 = 0, 0
    while f0 <= 0:
        f += f0
        ans0 = [0] * m
        for i in range(m):
            x, y = x0[i], y0[i]
            for w, _, f1, _, j in R[y]:
                if x == w and i == j:
                    ans0[i] = 2 * f1 + c0[i]  # compute actual flow
                    break
        f0 = min_cost_flow(s, t, 1)
    if -((f + (1 << 20)) // z) ^ v:  # check if solution is valid
        ok = 0
ans = "Possible" if ok else "Impossible"
print(ans)
if not ok:
    exit()
ans = ans0
sys.stdout.write(" ".join(map(str, ans)))


# https://github.com/VaHiX/CodeForces/