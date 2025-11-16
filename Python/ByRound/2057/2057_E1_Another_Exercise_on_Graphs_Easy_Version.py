# Problem: CF 2057 E1 - Another Exercise on Graphs (Easy Version)
# https://codeforces.com/contest/2057/problem/E1

"""
Algorithm: 
This solution uses a combination of Minimum Spanning Tree (MST) and BFS-based shortest path computation to solve the problem of finding k-th maximum edge weight among all paths between two nodes.

Key Techniques:
1. Kruskal's algorithm with DSU (Disjoint Set Union) to build MST
2. BFS with modified edge weights to compute shortest distances in MST
3. Binary search or direct iteration over MST edges to find k-th maximum edge weight

Time Complexity: O(M * log(M) + N * M + Q * M)
Space Complexity: O(N + M)

The approach works by:
1. Sorting edges by weight and building the MST using Kruskal's algorithm
2. For each edge in the MST, running BFS to compute distances in the MST with that edge as threshold
3. For each query, finding the minimum threshold edge weight that allows a path of at most k edges
"""

import os
import sys
from io import BytesIO, IOBase

from _collections import deque

BUFSIZE = 8192


class FastIO(IOBase):
    newlines = 0

    def __init__(self, file):
        self._fd = file.fileno()
        self.buffer = BytesIO()
        self.writable = "x" in file.mode or "r" not in file.mode
        self.write = self.buffer.write if self.writable else None

    def read(self):
        while True:
            b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
            if not b:
                break
            ptr = self.buffer.tell()
            self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
        self.newlines = 0
        return self.buffer.read()

    def readline(self):
        while self.newlines == 0:
            b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
            self.newlines = b.count(b"\n") + (not b)
            ptr = self.buffer.tell()
            self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
        self.newlines -= 1
        return self.buffer.readline()

    def flush(self):
        if self.writable:
            os.write(self._fd, self.buffer.getvalue())
            self.buffer.truncate(0), self.buffer.seek(0)


class IOWrapper(IOBase):
    def __init__(self, file):
        self.buffer = FastIO(file)
        self.flush = self.buffer.flush
        self.writable = self.buffer.writable
        self.write = lambda s: self.buffer.write(s.encode("ascii"))
        self.read = lambda: self.buffer.read().decode("ascii")
        self.readline = lambda: self.buffer.readline().decode("ascii")


if sys.version_info[0] < 3:
    sys.stdin = BytesIO(os.read(0, os.fstat(0).st_size))
else:
    sys.stdin, sys.stdout = IOWrapper(sys.stdin), IOWrapper(sys.stdout)

file = sys.stdin
if os.environ.get("USER") == "loic":
    file = open("data.in")

line = lambda: file.readline().split()
ui = lambda: int(line()[0])
mi = lambda: map(int, line())
li = lambda: list(mi())
lsi = lambda: list(map(int, line()[0]))


class DSU:
    def __init__(self, limit):
        self.par = list(range(limit))
        self.sz = [1] * limit

    def leader(self, u):
        lead = u
        while lead != self.par[lead]:
            lead = self.par[lead]

        node = u
        while node != lead:
            self.par[node], node = lead, self.par[node]

        return lead

    def union(self, u, v):
        u = self.leader(u)
        v = self.leader(v)
        if u != v:
            if self.sz[u] < self.sz[v]:
                u, v = v, u
            self.par[v] = u
            self.sz[u] += self.sz[v]

    def size(self, u):
        return self.sz[self.leader(u)]


def bs_pred_r(predicate, low, high):
    l = low
    r = high
    while l < r:
        mid = l + (r - l) // 2
        if predicate(mid) < 1:
            l = mid + 1
        else:
            r = mid
    return l


def solve():
    res = []

    A.sort(key=lambda e: e[2]) # Sort edges by weight
    dsu = DSU(N)

    def dfs(start, dist, inf):
        q = deque([start])
        dist[start] = 0

        while q:
            n = q.popleft()

            for ch, w in g[n]:
                nw = 1 if w > inf else 0 # Weight of edge in BFS traversal
                if dist[n] + nw < dist[ch]:
                    dist[ch] = dist[n] + nw
                    if nw == 1:
                        q.append(ch)
                    else:
                        q.appendleft(ch)

    dist = [[1 << 30 for _ in range(N)] for _ in range(N)]

    c = 0
    edges = []
    for u, v, w in A:
        if dsu.leader(u) != dsu.leader(v):
            dsu.union(u, v)

            dfs(u, dist[c], w) # Run BFS to compute distances in the MST with current edge as threshold
            edges.append(w)
            c += 1

    for _ in range(Q):
        a, b, k = mi()
        a -= 1
        b -= 1

        mn = 1 << 30
        for i in range(len(edges)):
            if dist[i][a] + dist[i][b] <= k - 1 and edges[i] < mn:
                mn = edges[i]

        res.append(mn)

    return " ".join(str(v) for v in res)


for test in range(1, ui() + 1):
    N, M, Q = mi()
    g = [[] for _ in range(N)]
    A = []

    for m in range(M):
        u, v, w = mi()
        u -= 1
        v -= 1
        g[u].append((v, w))
        g[v].append((u, w))
        A.append((u, v, w))

    print(solve())

file.close()


# https://github.com/VaHiX/CodeForces/