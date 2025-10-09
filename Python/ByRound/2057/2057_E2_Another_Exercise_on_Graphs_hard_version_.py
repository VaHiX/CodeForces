# Contest 2057, Problem E2: Another Exercise on Graphs (hard version)
# URL: https://codeforces.com/contest/2057/problem/E2

import sys
import os
from io import BytesIO, IOBase
from _collections import deque
from random import randint
import time

# region fastio
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
#######################################################################


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


def conv2D(a, b):
    return a * N + b


def conv3D(a, b, c):
    return a * N * N + b * N + c


def solve():
    res = []

    A.sort(key=lambda e: e[2])
    dsu = DSU(N)

    dist = [1 << 30 for _ in range(N**2)]
    for u in range(N):
        dist[conv2D(u, u)] = 0
    for u, v, w in A:
        dist[conv2D(u, v)] = 1
        dist[conv2D(v, u)] = 1

    for k in range(N):
        for i in range(N):
            for j in range(i + 1, N):
                dist[conv2D(i, j)] = dist[conv2D(j, i)] = min(
                    dist[conv2D(i, j)], dist[conv2D(i, k)] + dist[conv2D(k, j)]
                )

    best = [0 for _ in range(N**3)]

    for u, v, w in A:
        if dsu.leader(u) != dsu.leader(v):
            dsu.union(u, v)

            for i in range(N):
                for j in range(i + 1, N):
                    idx2D = conv2D(i, j)
                    if (
                        dist[idx2D] > dist[conv2D(i, u)] + dist[conv2D(v, j)]
                        or dist[idx2D] > dist[conv2D(i, v)] + dist[conv2D(u, j)]
                    ):
                        dist[idx2D] -= 1
                        dist[conv2D(j, i)] -= 1
                        best[conv3D(i, j, dist[idx2D])] = w

    for _ in range(Q):
        a, b, k = mi()
        a -= 1
        b -= 1

        a, b = min(a, b), max(a, b)
        res.append(best[conv3D(a, b, k - 1)])

    return " ".join(str(v) for v in res)


for test in range(1, ui() + 1):
    N, M, Q = mi()
    A = []

    for m in range(M):
        u, v, w = mi()
        u -= 1
        v -= 1
        A.append((u, v, w))

    print(solve())

file.close()
