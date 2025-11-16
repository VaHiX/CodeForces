# Problem: CF 1877 E - Autosynthesis
# https://codeforces.com/contest/1877/problem/E

"""
Algorithm: Graph Coloring and Cycle Detection
Purpose: Determine if we can color nodes in a directed graph such that for each node, 
         the color of the node equals the value of the element it points to, 
         and each node's color represents the number of times it's circled.
Time Complexity: O(n)
Space Complexity: O(n)

This problem can be interpreted as a graph coloring problem where:
- Each element a[i] points to node (a[i]-1) in a directed graph
- We need to assign colors (0 or 1) to nodes such that:
  - If a node has color 0, the node it points to has color 1
  - If a node has color 1, the node it points to has color 0
- If any odd-length cycle exists, it's impossible to 2-color it, thus return -1
- Otherwise, collect all nodes with color 0 for output
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

    par = [None] * N  # parent array: where each node points to
    out_deg = [0] * N  # out-degree of each node
    for i in range(N):
        par[i] = A[i] - 1  # convert to 0-based indexing
        out_deg[A[i] - 1] += 1  # count incoming edges

    col = [-1] * N  # color array: -1 = unvisited, 0 or 1 = colors
    q = deque([n for n, val in enumerate(out_deg) if val == 0])  # nodes with no incoming edges

    # BFS to color nodes with no incoming edges
    while q:
        n = q.pop()

        if col[n] == -1:
            col[n] = 0

        p = par[n]
        if p is not None:
            if col[n] == 0:
                col[p] = 1  # assign opposite color

            out_deg[p] -= 1  # reduce in-degree
            if out_deg[p] == 0:
                q.appendleft(p)  # add to queue if in-degree becomes 0

    # Handle cycles: process unvisited nodes
    for st in range(N):
        if col[st] != -1:
            continue

        # Find cycle
        n = st
        cyc = []
        while True:
            cyc.append(n)
            n = par[n]
            if n == st:
                break

        # If all nodes in cycle are unvisited
        if all(col[n] == -1 for n in cyc):
            # Odd-length cycle: impossible to 2-color
            if len(cyc) % 2 == 1:
                return str(-1)
            # Even-length cycle: assign alternating colors starting with 0
            col[cyc[0]] = 0
            for i in range(1, len(cyc)):
                col[cyc[i]] = col[cyc[i - 1]] ^ 1
        else:
            # Find reference point to break cycle properly
            for i in range(len(cyc)):
                if col[cyc[i]] == -1 and col[cyc[i - 1]] == 1:
                    ref = i
                    break

            cyc = cyc[ref:] + cyc[:ref]  # rotate cycle
            # Assign colors based on previous node
            for i in range(len(cyc)):
                if col[cyc[i]] == -1:
                    col[cyc[i]] = col[cyc[i - 1]] ^ 1

    # Collect all nodes with color 0 (those to be circled)
    pos = [i for i, val in enumerate(col) if val == 0]
    pos.sort()  # sort indices
    res = [A[i] for i in pos]  # get elements

    return str(len(res)) + "\n" + " ".join(str(v) for v in res)


for test in range(1, 1 + 1):
    N = ui()
    A = li()

    print(solve())

file.close()


# https://github.com/VaHiX/CodeForces/