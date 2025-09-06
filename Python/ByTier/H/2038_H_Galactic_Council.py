# Contest 2038, Problem H: Galactic Council
# URL: https://codeforces.com/contest/2038/problem/H

import sys
from collections import deque

class MCMF:
    INF = float('inf')
    
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
        self.gph[u].append(self.Edge(v, c, w, len(self.gph[v])))
        self.gph[v].append(self.Edge(u, 0, -w, len(self.gph[u]) - 1))
    
    def shortest_path(self):
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
                if self.dist[edge.v] > self.dist[x] + edge.w:
                    self.dist[edge.v] = max(self.dist[x] + edge.w, -self.INF)
                    self.par[edge.v] = edge.r
                    if not self.inq[edge.v]:
                        self.inq[edge.v] = True
                        if Q and self.dist[Q[0]] > self.dist[edge.v]:
                            Q.appendleft(edge.v)
                        else:
                            Q.append(edge.v)
        return self.dist[self.snk] != self.INF
    
    def flow(self, src, snk):
        self.src = src
        self.snk = snk
        cost = 0
        flow = 0
        while self.shortest_path():
            val = self.INF
            x = snk
            while x != src:
                edge = self.gph[x][self.par[x]]
                val = min(val, self.gph[edge.v][edge.r].c)
                x = edge.v
            
            x = snk
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
N, M = map(int, input[ptr:ptr+2])
ptr += 2
p = list(map(int, input[ptr:ptr+M]))
ptr += M
p = [x-1 for x in p]

a = []
for _ in range(N):
    row = list(map(int, input[ptr:ptr+M]))
    ptr += M
    a.append(row)

b = [[0]*M for _ in range(N)]
mx_val = 1
for i in range(M):
    if i > 0 and p[i-1] < p[i]:
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

for i in range(M):
    mcmf.add_edge(S, N*M+i, 1, 0)
for i in range(M):
    for j in range(N):
        mcmf.add_edge(N*M+i, j*M+i, 1, mx_a - a[j][i])
for i in range(M):
    for j in range(N):
        now = j*M + i
        nxt = E if i == M-1 else j*M + i + 1
        if j == p[i]:
            mcmf.add_edge(SP, nxt, b[j][i], 0)
            mcmf.add_edge(now, EP, b[j][i], 0)
            wsum += b[j][i]
        else:
            mcmf.add_edge(now, nxt, b[j][i], 0)

mcmf.add_edge(E, S, float('inf'), 0)

flow1, cost1 = mcmf.flow(SP, EP)

if flow1 != wsum:
    print(-1)
    exit()

flow2, cost2 = mcmf.flow(S, E)

if flow2 != M:
    print(-1)
    exit()

ans = [0]*M
for i in range(M):
    for edge in mcmf.gph[N*M + i]:
        if edge.v != S and edge.c == 0:
            ans[i] = edge.v // M
            break

print(' '.join(map(str, [x+1 for x in ans])))