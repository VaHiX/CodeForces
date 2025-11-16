# Problem: CF 1850 H - The Third Letter
# https://codeforces.com/contest/1850/problem/H

"""
Algorithm: Union-Find with Distance Tracking (DSU with path compression and distance tracking)
Purpose: Determine if a set of constraints on relative positions of soldiers can be satisfied.
Time Complexity: O(m * α(n)) where α is the inverse Ackermann function, nearly constant.
Space Complexity: O(n) for storing the DSU structure.

The problem is modeled as a graph where each soldier is a node and each constraint represents
a directed edge with a weight indicating relative distance. We use a Union-Find data structure
with distance tracking to detect contradictions in the constraints.

Key idea:
- For each constraint (a, b, d): soldier a should be at position d units relative to soldier b
- We track the "distance" from each node to its root in the DSU
- When merging two sets, we update the distance of the new root
- If we try to merge two nodes that are already in the same set but with conflicting distances, we return NO
"""

import os
import sys
from io import BytesIO, IOBase

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


class DSU:
    def __init__(self, n):
        # Initialize parent array and distance array
        self.val = list(range(n + 1))
        self.dis = [0] * (n + 1)

    def find(self, x):
        # Path compression with distance adjustment
        d, st = 0, []
        while x != self.val[x]:
            st.append(x)
            x = self.val[x]
        while st:
            y = st.pop()
            self.val[y] = x
            self.dis[y] += d
            d = self.dis[y]
        return x

    def merge(self, x, y, d):
        # Merge two sets and adjust distances
        xz = self.find(x)
        yz = self.find(y)
        if xz != yz:
            # If not in same set, merge them and update the distance
            self.val[xz] = yz
            self.dis[xz] = d - self.dis[x] + self.dis[y]
        elif self.dis[x] - self.dis[y] != d:
            # If already in same set but contradicting distance, return 1 (failure)
            return 1


pyin = lambda: map(int, input().split())


def The_Third_Letter():
    n, m = pyin()
    U = DSU(n)
    ans = "YES"
    for i in range(m):
        ai, bi, di = pyin()
        # Check for contradiction in constraints
        if U.merge(ai, bi, di):
            ans = "NO"
    return ans


for _ in range(int(input())):
    print(The_Third_Letter())


# https://github.com/VaHiX/CodeForces/