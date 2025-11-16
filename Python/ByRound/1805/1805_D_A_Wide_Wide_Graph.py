# Problem: CF 1805 D - A Wide, Wide Graph
# https://codeforces.com/contest/1805/problem/D

"""
Algorithm: 
- For each k from 1 to n, we need to find the number of connected components in graph G_k.
- G_k has an edge between u and v if and only if the distance between u and v in the original tree is at least k.
- The key idea is to find the diameter of the tree and use it to efficiently compute the number of connected components for each k.
- We perform two DFS traversals to find the farthest node from an arbitrary node (first DFS), then find the farthest node from that node (second DFS).
- The maximum depth of each node in these traversals helps compute the distances from the center of the tree.
- We use counting sort logic to track how many nodes have a certain distance.
- Time complexity: O(n)
- Space complexity: O(n)

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


def dfs(g, st):
    q = deque([st])
    vis = [0] * N
    vis[st] = 1
    dist = [0] * N
    far = st

    while q:
        n = q.pop()

        for ch in g[n]:
            if not vis[ch]:
                vis[ch] = 1
                q.append(ch)
                dist[ch] = dist[n] + 1
                if dist[ch] > dist[far]:
                    far = ch

    return dist, far


def solve():

    g = G
    start = 0

    _, f = dfs(g, start)
    dist_f, s = dfs(g, f)
    dist_s, _ = dfs(g, s)

    dist = [max(a, b) for a, b in zip(dist_f, dist_s)]

    c = [0] * (N + 1)
    for val in dist:
        c[val + 1] += 1

    n = 1
    res = []

    for i in range(1, N + 1):
        n += c[i]
        res.append(min(n, N))

    return " ".join(str(v) for v in res)


for test in range(1, 1 + 1):
    N = ui()

    G = [[] for _ in range(N)]
    for _ in range(N - 1):
        u, v = mi()
        u -= 1
        v -= 1
        G[u].append(v)
        G[v].append(u)

    print(solve())

file.close()


# https://github.com/VaHiX/CodeForces/