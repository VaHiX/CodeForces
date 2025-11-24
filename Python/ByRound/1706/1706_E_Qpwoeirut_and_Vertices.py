# Problem: CF 1706 E - Qpwoeirut and Vertices
# https://codeforces.com/contest/1706/problem/E

"""
Algorithm: Union-Find with weights + Sparse Table
Time Complexity: O(n log n + q log n) where n is number of vertices and q is number of queries
Space Complexity: O(n) for disjoint set and sparse table structures

This solution uses a Union-Find data structure to track connectivity as edges are added.
We build a sparse table to efficiently answer range maximum queries on the weights
required to connect vertex pairs.
"""

import os
import sys
import threading
from io import BytesIO, IOBase

threading.stack_size(250 * 1024 * 1024)
sys.setrecursionlimit(5000)


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


sys.stdin, sys.stdout = IOWrapper(sys.stdin), IOWrapper(sys.stdout)
input = lambda: sys.stdin.readline().rstrip("\r\n")


class DisjointSetWithWeights:
    def __init__(self, size):
        # Initialize parent array and size array
        self.U = [[i, 1] for i in range(size)]
        # Initialize weight array to track max weight needed to connect components
        self.W = [10**9 for i in range(size)]

    def root(self, e):
        u = self.U[e]

        if u[0] != e:
            # Path compression
            return self.root(u[0])

        return u

    def union(self, first, second, weight):
        uFirst, uSecond = self.root(first), self.root(second)

        if uFirst == uSecond:
            return False

        # Union by size
        if uFirst[1] < uSecond[1]:
            uFirst, uSecond = uSecond, uFirst
            first, second = second, first

        if uSecond[0] != uFirst[0]:
            # Update weight needed to connect the two components
            self.W[uSecond[0]] = weight
            uSecond[0] = uFirst[0]
            uFirst[1] += uSecond[1]

        return True

    def maxWeight(self, s, e):
        w = 0

        while s != e:
            # Move the pointer with smaller weight to parent
            if self.W[s] < self.W[e]:
                s, w = self.U[s][0], self.W[s]
            else:
                e, w = self.U[e][0], self.W[e]

        return w


class SparseTable:
    def __init__(self, A, F):
        self.A = A
        self.F = F

        self.buildLG()
        self.buildST()

    def buildLG(self):
        # Precompute log values for range queries
        self.LG = []
        lg, V = 0, 1
        for e in range(len(self.A) + 1):
            if V * 2 <= e:
                V *= 2
                lg += 1
            self.LG.append(lg)

    def buildST(self):
        n = len(self.A)
        self.ST = []
        length = 1
        while length <= n:
            if length == 1:
                self.ST.append(self.A)
            else:
                # Build sparse table with range queries
                self.ST.append(
                    [
                        self.F(self.ST[-1][s], self.ST[-1][s + length // 2])
                        for s in range(n - length + 1)
                    ]
                )

            length <<= 1

    def query(self, l, r):
        if l == r:
            return self.ST[0][l]

        if l > r:
            l, r = r, l

        # Get range size and compute query
        e = self.LG[r - l + 1]
        return self.F(self.ST[e][l], self.ST[e][r - 2**e + 1])


T = int(input())
for _ in range(T):
    n, m, q = map(int, input().split())

    # Create DSU for tracking connected components
    dsu = DisjointSetWithWeights(n + 1)

    # Process edges in order to build connectivity information
    for i in range(m):
        s, e = map(int, input().split())
        dsu.union(s, e, i)

    # Get the maximum weight needed to connect consecutive vertices
    W = [dsu.maxWeight(i, i + 1) for i in range(1, n)]

    # Build sparse table for efficient range maximum queries
    ST = SparseTable(W, max)

    R = []
    for i in range(q):
        a, b = map(int, input().split())
        if a == b:
            # Same vertex, no edges needed
            R.append(0)
        else:
            # Query range and add 1 to get minimum edge needed
            R.append(ST.query(a - 1, b - 2) + 1)

    print(" ".join(str(r) for r in R))


# https://github.com/VaHiX/CodeForces/