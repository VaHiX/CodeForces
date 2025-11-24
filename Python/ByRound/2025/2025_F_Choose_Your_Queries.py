# Problem: CF 2025 F - Choose Your Queries
# https://codeforces.com/contest/2025/problem/F

"""
F. Choose Your Queries

Purpose:
This code processes a series of queries on an array of size n, where each query involves choosing one of two elements (x_i or y_i) and adding or subtracting 1 to it.
The goal is to minimize the final sum of all array elements while ensuring they remain non-negative at every step.

Algorithm:
- Model the problem as a graph traversal with DFS-like logic to build a spanning tree of edges (queries), and assign directions to minimize the cumulative sum.
- Uses DFS-style iteration to process nodes in topological order, assigning directions for each edge in such a way that we minimize future increments.
- Maintains a count of how many times an element is incremented or decremented.

Time Complexity: O(n + q)
Space Complexity: O(n + q)

Techniques:
- Graph traversal using stack-based DFS to process nodes
- Direction assignment to minimize final sum
- Efficient input/output handling with buffered I/O

"""

standard_input, packages, output_together = 1, 1, 0
dfs, hashing, read_from_file = 1, 0, 0
de = 1
if 1:
    if standard_input:
        import os
        import sys

        input = lambda: sys.stdin.readline().strip()
        import math

        inf = math.inf

        def I():
            return input()

        def II():
            return int(input())

        def MII():
            return map(int, input().split())

        def LI():
            return list(input().split())

        def LII():
            return list(map(int, input().split()))

        def LFI():
            return list(map(float, input().split()))

        def GMI():
            return map(lambda x: int(x) - 1, input().split())

        def LGMI():
            return list(map(lambda x: int(x) - 1, input().split()))

    if packages:
        import os
        import random
        from io import BytesIO, IOBase

        BUFSIZE = 4096
    if output_together:

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

        sys.stdout = IOWrapper(sys.stdout)
    if dfs:
        from types import GeneratorType

        def bootstrap(f, stk=[]):
            def wrappedfunc(*args, **kwargs):
                if stk:
                    return f(*args, **kwargs)
                else:
                    to = f(*args, **kwargs)
                    while True:
                        if type(to) is GeneratorType:
                            stk.append(to)
                            to = next(to)
                        else:
                            stk.pop()
                            if not stk:
                                break
                            to = stk[-1].send(to)
                    return to

            return wrappedfunc

    if hashing:
        RANDOM = random.getrandbits(20)

        class Wrapper(int):
            def __init__(self, x):
                int.__init__(x)

            def __hash__(self):
                return super(Wrapper, self).__hash__() ^ RANDOM

    if read_from_file:
        file = open("input.txt", "r", encoding="utf-16").readline().strip()
        fin = open(file, "r")
        input = lambda: fin.readline().strip()
        output_file = open("output.txt", "w")

        def fprint(*args, **kwargs):
            print(*args, **kwargs, file=output_file)

    if de:

        def debug(*args, **kwargs):
            print("\033[92m", end="")
            print(*args, **kwargs)
            print("\033[0m", end="")

    fmax = lambda x, y: x if x > y else y
    fmin = lambda x, y: x if x < y else y

    class lst_lst:
        def __init__(self, n) -> None:
            self.n = n
            self.pre = []
            self.cur = []
            self.lst = [-1] * n

        def append(self, i, j):
            self.pre.append(self.lst[i])
            self.lst[i] = len(self.cur)
            self.cur.append(j)

        def iterate(self, i):
            tmp = self.lst[i]
            while tmp != -1:
                yield self.cur[tmp]
                tmp = self.pre[tmp]


n, q = MII()
us = [-1] * q
vs = [-1] * q
path = [[] for _ in range(n)]
for i in range(q):
    us[i], vs[i] = GMI()  # Convert to 0-based indexing
    path[us[i]].append(i)
    path[vs[i]].append(i)
parent = [-1] * n
vis = [0] * n
order = []
stk = []
for i in range(n):
    if parent[i] == -1:
        stk.append(i)
        while stk:
            u = stk.pop()
            for idx in range(vis[u], len(path[u])):
                vis[u] += 1
                eid = path[u][idx]
                v = us[eid] + vs[eid] - u  # Determine adjacent node to current node u, based on the query edge
                if v != i and parent[v] == -1:
                    parent[v] = eid
                    stk.append(u)
                    stk.append(v)
                    break
            else:
                order.append(u)  # Add node `u` to processing order since it is done with neighbors
dirs = [-1] * q
cur = [0] * n
for u in order:
    cur = -1  # Initially no direction assigned yet (will be tracked)
    for eid in path[u]:
        if dirs[eid] == -1 and parent[u] != eid:  # Not visited, not part of DFS tree edge
            if cur == -1:
                cur = eid  # First unvisited edge gets chosen to set direction later
            else:
                dirs[cur] = 1 if us[cur] == u else 0  # Assign direction based on which node is active
                dirs[eid] = 1 if us[eid] == u else 0
                cur = -1  # After assigning two directions, reset for next potential pair
    if cur != -1 and parent[u] != -1:  # Ensure there is a valid direction if needed (edge to parent)
        eid = parent[u]
        dirs[cur] = 1 if us[cur] == u else 0
        dirs[eid] = 1 if us[eid] == u else 0
cur = [0] * n
outs = []
for i in range(q):
    outs.append("yx"[dirs[i]] + "+-"[cur[us[i]] if dirs[i] else cur[vs[i]]]) # Output result for query `i`
    if dirs[i]:
        cur[us[i]] ^= 1  # Update count at x
    else:
        cur[vs[i]] ^= 1  # Update count at y
print("\n".join(outs))


# https://github.com/VaHiX/codeForces/