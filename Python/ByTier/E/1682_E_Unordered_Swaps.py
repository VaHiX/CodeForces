# Problem: CF 1682 E - Unordered Swaps
# https://codeforces.com/contest/1682/problem/E

"""
Algorithm: Topological Sort with Cycle Detection
- Time Complexity: O(n + m log m) where n is the size of permutation and m is the number of swaps
- Space Complexity: O(n + m) for storing graph and auxiliary data structures

The approach:
1. Identify connected components in the permutation (cycles)
2. For each cycle, sort the edges based on their order in the cycle
3. Build a topological graph of edges 
4. Perform topological sort to get the correct sequence

This is essentially about finding a valid order of swaps that transforms the permutation into sorted order.
"""

import os
import sys
from collections import deque
from io import BytesIO, IOBase

BUFSIZE = 8192


class FastIO(IOBase):
    newlines = 0

    def __init__(self, file):
        self._file = file
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


sys.stdin, sys.stdout = IOWrapper(sys.stdin), IOWrapper(sys.stdout)
input = lambda: sys.stdin.readline().rstrip("\r\n")


def read_int_list():
    return list(map(int, input().split()))


def read_int_tuple():
    return tuple(map(int, input().split()))


def read_int():
    return int(input())


def solve(n, nums, m, edges):
    seen = [False] * n
    gs = []
    for i in range(n):
        if seen[i]:
            continue
        gl = []
        # Find a cycle starting from node i
        while not seen[i]:
            gl.append(i)
            seen[i] = True
            i = nums[i]
        if len(gl) > 1:
            gs.append(gl)

    # For each cycle, sort the edges based on their position in the cycle
    for group in gs:
        d = {u: i for i, u in enumerate(group)}
        for u in group:
            # Sort edges by position in cycle (for topological ordering)
            edges[u].sort(key=lambda t: (d[t[0]] - d[u]) % n)

    # Build topological graph of edges
    top_graph = [[] for _ in range(m)]
    indeg = [0] * m
    for es in edges:
        if len(es) < 2:
            continue
        # Connect consecutive edges in a cycle
        for i in range(len(es) - 1):
            u, v = es[i][1], es[i + 1][1]  # u and v are indices of the swaps
            top_graph[u].append(v)
            indeg[v] += 1
    q = deque([u for u in range(m) if indeg[u] == 0])  # Start with edges with no dependency
    res = []
    while q:
        u = q.popleft()
        res.append(u + 1)  # Convert to 1-indexed
        for v in top_graph[u]:
            indeg[v] -= 1
            if indeg[v] == 0:
                q.append(v)
    print(*res)


def main():
    for _ in range(1):
        n, m = read_int_tuple()
        nums = [x - 1 for x in read_int_list()]  # Convert to 0-indexed
        edges = [[] for _ in range(n)]
        for i in range(m):
            u, v = read_int_tuple()
            edges[u - 1].append((v - 1, i))  # Store edge and its index
            edges[v - 1].append((u - 1, i))
        solve(n, nums, m, edges)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/