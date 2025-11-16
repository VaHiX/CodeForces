# Problem: CF 1819 C - The Fox and the Complete Tree Traversal
# https://codeforces.com/contest/1819/problem/C

"""
Problem: The Fox and the Complete Tree Traversal
Algorithm: DFS to find diameter, then construct a traversal path
Time Complexity: O(n) - DFS traversal and path construction
Space Complexity: O(n) - storage for adjacency list, visited info, and path

The fox can jump from vertex v to u if distance between them is <= 2.
We need to find a cycle that visits all vertices with this constraint.
This is equivalent to finding a Hamiltonian cycle in the "jump graph"
where vertices are connected if their distance is <= 2.

Key insight:
1. If the tree has a diameter path of length >= 3, then there's a valid cycle.
2. We use DFS to find the diameter of the tree.
3. Then we construct a traversal by walking the diameter and visiting leaves.
4. The traversal alternates direction on the diameter and processes leaves accordingly.
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


ii = lambda: int(input())
mii = lambda: map(int, input().split())
fii = lambda: map(float, input().split())
lmii = lambda: list(map(int, input().split()))
i2c = lambda n: chr(ord("a") + n)
c2i = lambda c: ord(c) - ord("a")


mod = 10**9 + 7


def solve():
    n = ii()
    d = [[] for _ in range(n)]
    for i in range(n - 1):
        x, y = mii()
        x, y = x - 1, y - 1
        d[x].append(y)
        d[y].append(x)

    def dfs(v):
        dis = [-1] * n
        dis[v] = 0
        stack = [v]
        while stack:
            x = stack.pop()
            for y in d[x]:
                if dis[y] == -1:
                    stack.append(y)
                    dis[y] = dis[x] + 1
        return dis

    dis0 = dfs(0)
    v0 = dis0.index(max(dis0))
    dis = dfs(v0)
    vn = dis.index(max(dis))
    dia = [vn]
    while dia[-1] != v0:
        for v in d[dia[-1]]:
            if dis[v] < dis[dia[-1]]:
                dia.append(v)
                break
    dia.reverse()
    S = set(dia)
    res1, res2 = [], []
    for i in range(len(dia)):
        if i & 1 == 0:
            res1.append(dia[i])
        else:
            res2.append(dia[i])
        if i == len(dia) - 1:
            break
        x = dia[i + 1]
        for y in d[x]:
            if y in S:
                continue
            if len(d[y]) > 1:
                print("No")
                return
            if i & 1 == 0:
                res1.append(y)
            else:
                res2.append(y)
    res2.reverse()
    res1 += res2
    for i in range(n):
        res1[i] += 1
    print("Yes")
    print(*res1)


for _ in range(1):
    solve()


# https://github.com/VaHiX/CodeForces/