# Problem: CF 1975 E - Chain Queries
# https://codeforces.com/contest/1975/problem/E

"""
Algorithm: Tree Chain Detection
Approach:
- For each query, toggle the color of a vertex
- After each toggle, check if all black vertices form a chain
- A chain means all black vertices are connected in a single path
- To determine this efficiently:
  - Maintain degree counts for each vertex in the subtree
  - Track vertices with degree 1, 2, and >=3 in the subtree
  - Monitor the number of black parents for black vertices
  - A valid chain has exactly 1 or 2 endpoints and no vertices with degree >= 3

Time Complexity: O(n + q) amortized per test case
Space Complexity: O(n) for storing tree structure, colors, and auxiliary arrays
"""

import os
import sys
from io import BytesIO, IOBase

from collections import deque

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


def solve():

    res = []

    g = G
    start = 0

    seen = [-1] * len(g)
    q = deque([start])
    seen[start] = 0

    par = [-1] * N
    col = A.copy() + [0]
    sub = [0] * (N + 1)

    # Build parent and subtree degree information
    while q:
        n = q[-1]

        chs = g[n]
        nb = seen[n]
        if nb == len(chs):
            q.pop()

            if col[n] == 1:
                sub[par[n]] += 1
        else:
            ch = chs[nb]
            if seen[ch] == -1:
                seen[ch] = 0
                q.append(ch)
                par[ch] = n
            seen[n] += 1

    one = 0
    two = set()
    more = 0
    p = 0

    # Count nodes by their subtree degrees
    for n in range(N):
        if sub[n] == 1:
            one += 1
        elif sub[n] == 2:
            two.add(n)
        elif sub[n] >= 3:
            more += 1
        if col[n] == 1 and col[par[n]] == 0:
            p += 1
    if sub[-1] == 1:
        one += 1

    # Process queries
    for _ in range(Q):
        n = ui()
        n -= 1

        # Toggling color
        if col[n] == 0:
            sub[par[n]] += 1
            if sub[par[n]] == 1:
                one += 1
            elif sub[par[n]] == 2:
                one -= 1
                two.add(par[n])
            elif sub[par[n]] == 3:
                two.remove(par[n])
                more += 1

            if col[par[n]] == 0:
                p += 1
            p -= sub[n]

        else:
            sub[par[n]] -= 1
            if sub[par[n]] == 0:
                one -= 1
            elif sub[par[n]] == 1:
                two.remove(par[n])
                one += 1
            elif sub[par[n]] == 2:
                more -= 1
                two.add(par[n])

            if col[par[n]] == 0:
                p -= 1
            p += sub[n]

        col[n] ^= 1  # Toggle color

        # Check if black vertices form a chain
        if len(two) == 0 and more == 0 and p == 1:
            res.append("Yes")
        elif len(two) == 1 and col[par[next(iter(two))]] == 0 and more == 0 and p == 1:
            res.append("Yes")
        else:
            res.append("No")

    return "\n".join(v for v in res)


for test in range(1, ui() + 1):
    N, Q = mi()
    A = li()
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