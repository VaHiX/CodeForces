# Problem: CF 2064 E - Mycraft Sand Sort
# https://codeforces.com/contest/2064/problem/E

"""
E. Mycraft Sand Sort

Purpose:
This code solves a problem involving gravity sorting of a permutation with colored sand blocks. 
It determines how many different pairs (p', c') can produce the same final layout as given (p, c).
The core idea uses Disjoint Set Union (DSU) and simulation of the falling sand process to compute
the number of valid permutations that result in an identical sand layout.

Algorithms/Techniques:
- Gravity Sort Simulation: Each element p[i] represents the height of sand blocks,
  color c[i] indicates their color.
- Disjoint Set Union (DSU): Tracks connected components where sand can fall together.
- Modular Arithmetic: All computations are done modulo 998244353.

Time Complexity:
O(N * α(N)) where α is the inverse Ackermann function (nearly constant).
Space Complexity:
O(N)

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


def solve():
    res = 1
    prev = [i - 1 for i in range(N)]
    nxt = [i + 1 for i in range(N)]
    dsu = DSU(N)
    arr = [0] * N
    # Create mapping from values in permutation to their positions
    for i, val in enumerate(P):
        arr[val - 1] = i
    # Connect adjacent indices if their heights are equal in original array A
    for i in range(1, N):
        if A[i] == A[i - 1]:
            dsu.union(i - 1, i)
    
    # Process elements in order they appear in the permutation P
    for idx in arr:
        # Update linked list to remove current index from chain
        if nxt[idx] != N:
            prev[nxt[idx]] = prev[idx]
        if prev[idx] != -1:
            nxt[prev[idx]] = nxt[idx]
        
        # Join previous and next nodes if they share same height in A
        if prev[idx] != -1 and nxt[idx] != N and A[prev[idx]] == A[nxt[idx]]:
            dsu.union(prev[idx], nxt[idx])
        
        # Multiply result by the size of component that idx belongs to
        res = (res * dsu.size(idx)) % MOD
        
        # Decrement the size since this node is now "used"
        dsu.sz[dsu.leader(idx)] -= 1
    return str(res)


MOD = 998244353
for test in range(1, ui() + 1):
    N = ui()
    P = li()
    A = li()
    print(solve())
file.close()


# https://github.com/VaHiX/codeForces/