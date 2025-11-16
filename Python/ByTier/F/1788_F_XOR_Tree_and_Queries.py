# Problem: CF 1788 F - XOR, Tree, and Queries
# https://codeforces.com/contest/1788/problem/F

"""
Algorithm: XOR, Tree, and Queries
Approach:
1. Build a tree from the given edges and store XOR path conditions for each node.
2. Use BFS/DFS to assign values to nodes based on path conditions, checking for consistency.
3. If there's an inconsistency, output "No".
4. Use a global value to ensure all edge weights sum up to minimal XOR value.
5. Output edge weights by XORing adjacent node values.

Time Complexity: O(n + q)
Space Complexity: O(n + q)

The key idea is to represent each node's value in a way that respects XOR path conditions,
then assign values to edges by XORing adjacent node values.
"""

import os
import sys
from functools import reduce
from io import BytesIO, IOBase
from operator import xor

BUFSIZE = 4096
inf = float("inf")
if "PyPy" in sys.version:
    import pypyjit

    pypyjit.set_param("max_unroll_recursion=-1")


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


from types import GeneratorType


def bootstrap(f, stack=[]):
    def wrappedfunc(*args, **kwargs):
        if stack:
            return f(*args, **kwargs)
        else:
            to = f(*args, **kwargs)
            while True:
                if type(to) is GeneratorType:
                    stack.append(to)
                    to = next(to)
                else:
                    stack.pop()
                    if not stack:
                        break
                    to = stack[-1].send(to)
            return to

    return wrappedfunc


n, q = MII()
edges = []
degs = [0] * n
for _ in range(n - 1):
    u, v = GMI()
    edges.append([u, v])
    degs[u] ^= 1
    degs[v] ^= 1

xor_path = [[] for _ in range(n)]
for _ in range(q):
    u, v, w = MII()
    u -= 1
    v -= 1
    xor_path[u].append([v, w])
    xor_path[v].append([u, w])

ans = [0] * n
visited = [0] * n
idx = -1
for i in range(n):
    if not visited[i]:
        visited[i] = 1
        stack = [i]
        cnt = degs[i]
        while stack:
            u = stack.pop()
            for v, w in xor_path[u]:
                if not visited[v]:
                    visited[v] = 1
                    cnt ^= degs[v]
                    ans[v] = w ^ ans[u]
                    stack.append(v)
                elif ans[v] ^ ans[u] != w:
                    print("No")
                    exit()
        if cnt:
            idx = i

print("Yes")

if idx != -1:
    val = reduce(xor, [ans[u] ^ ans[v] for u, v in edges])
    ans[idx] ^= val
    stack = [idx]
    while stack:
        u = stack.pop()
        for v, w in xor_path[u]:
            if ans[v] ^ ans[u] != w:
                ans[v] = w ^ ans[u]
                stack.append(v)

print(*[ans[u] ^ ans[v] for u, v in edges])


# https://github.com/VaHiX/CodeForces/