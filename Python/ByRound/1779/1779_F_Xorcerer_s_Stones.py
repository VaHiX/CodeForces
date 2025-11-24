# Problem: CF 1779 F - Xorcerer's Stones
# https://codeforces.com/contest/1779/problem/F

"""
Code Purpose:
This code solves the "Xorcerer's Stones" problem where we need to clear all stones from a rooted tree using XOR spells.
The approach uses dynamic programming on trees to determine if it's possible to make all values zero, and then uses a backtracking approach to construct the sequence of operations.

Algorithms/Techniques:
1. Dynamic Programming on Trees - to determine if it's possible to achieve all zeros
2. Backtracking - to reconstruct the sequence of operations
3. Bit Manipulation - for XOR operations and state tracking

Time Complexity: O(n * M) where n is number of nodes and M is the maximum bit size (32)
Space Complexity: O(n * M) for the DP table and auxiliary arrays
"""

import os
import sys
from io import BytesIO, IOBase

BUFSIZE = 4096
inf = float("inf")


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


n = II()

A = LII()
parent = [-1] + LGMI()

edge = [[] for v in range(n)]
for i in range(1, n):
    edge[parent[i]].append(i)


sz = [1] * n
M = 32
dp = [[False] * M for i in range(n)]
for v in range(n - 1, -1, -1):
    tmp = [False] * M
    tmp[A[v]] = True
    for nv in edge[v]:
        ndp = [False] * M
        for i in range(M):
            for j in range(M):
                if tmp[i] & dp[nv][j]:
                    ndp[i ^ j] = True
        tmp = ndp
        sz[v] += sz[nv]
    if sz[v] & 1 == 0:
        tmp[0] = True
    dp[v] = tmp

if not dp[0][0]:
    exit(print(-1))

res = []
stack = [(0, 0)]
while stack:
    v, xx = stack.pop()

    if xx == 0 and sz[v] & 1 == 0:
        res.append(v)
        continue

    pre = [[-1] * M for i in range(len(edge[v]) + 1)]
    tmp = [False] * M
    tmp[A[v]] = True
    for i in range(len(edge[v])):
        nv = edge[v][i]
        n_tmp = [False] * M
        for x in range(M):
            for y in range(M):
                if tmp[x] & dp[nv][y]:
                    n_tmp[x ^ y] = True
                    pre[i + 1][x ^ y] = (x, y)
        tmp = n_tmp

    for i in range(len(edge[v]))[::-1]:
        nv = edge[v][i]
        xx, y = pre[i + 1][xx]
        stack.append((nv, y))

res = res[::-1] + [0, 0]
res = [v + 1 for v in res]
print(len(res))
print(*res)


# https://github.com/VaHiX/CodeForces/