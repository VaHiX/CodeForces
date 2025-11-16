# Problem: CF 1797 D - Li Hua and Tree
# https://codeforces.com/contest/1797/problem/D

"""
Algorithm: Heavy-Light Decomposition with Dynamic Tree Operations
Time Complexity: O((n + m) * log n)
Space Complexity: O(n)

This solution handles a tree with dynamic operations including:
1. Query the sum of importance in a subtree (operation 1)
2. Rotate the heavy child of a node up (operation 2)

The key techniques used:
- DFS traversal to build parent relationships and compute subtree sizes
- Heap-based storage of children to quickly identify heavy child
- Dynamic restructuring of the tree during rotation operations
- Path compression technique to maintain efficient updates

The heavy child is defined as the child with the largest subtree size.
In case of ties, the one with the smallest index is chosen.
"""

import os
import sys
from heapq import heappop, heappush
from io import BytesIO, IOBase


class IOWrapper(IOBase):
    def __init__(self, file):
        self.buffer = FastIO(file)
        self.flush = self.buffer.flush
        self.writable = self.buffer.writable
        self.write = lambda s: self.buffer.write(s.encode("ascii"))
        self.read = lambda: self.buffer.read().decode("ascii")
        self.readline = lambda: self.buffer.readline().decode("ascii")


BUFSIZE = 4096


class FastIO(IOBase):
    newlines = 0

    def __init__(self, file):
        self._fd = file.fileno()
        self.buffer = BytesIO()
        self.writable = "x" in file.mode or "r" not in file.mode
        self.write = self.buffer.write if self.writable else None

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

    def read(self):
        while True:
            b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
            if not b:
                break
            ptr = self.buffer.tell()
            self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
        self.newlines = 0
        return self.buffer.read()


sys.stdin = IOWrapper(sys.stdin)
sys.stdout = IOWrapper(sys.stdout)
input = lambda: sys.stdin.readline().rstrip("\r\n")


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


def GMI():
    return map(lambda x: int(x) - 1, input().split())


def LGMI():
    return list(map(lambda x: int(x) - 1, input().split()))


inf = float("inf")


n, m = MII()
nums = LII()
path = [[] for _ in range(n)]
for _ in range(n - 1):
    u, v = GMI()
    path[u].append(v)
    path[v].append(u)

parent = [None] * n
order = []
stack = [(-1, 0)]
while stack:
    p, u = stack.pop()
    parent[u] = p
    order.append(u)
    for v in path[u]:
        if v != p:
            stack.append((u, v))

order.reverse()
size = [1] * n
sons = [[] for _ in range(n)]
for idx in order:
    if parent[idx] != -1:
        size[parent[idx]] += size[idx]
        nums[parent[idx]] += nums[idx]
        heappush(sons[parent[idx]], [-size[idx], idx])

for _ in range(m):
    op, x = MII()
    x -= 1
    if op == 1:
        print(nums[x])
    elif size[x] > 1:
        u = parent[x]
        ms, v = heappop(sons[x])
        while parent[v] != x or ms != -size[v]:
            ms, v = heappop(sons[x])
        parent[v] = u
        parent[x] = v
        nums[x] -= nums[v]
        size[x] -= size[v]
        nums[v] += nums[x]
        size[v] += size[x]
        if u != -1:
            heappush(sons[u], [-size[v], v])
        heappush(sons[v], [-size[x], x])


# https://github.com/VaHiX/CodeForces/