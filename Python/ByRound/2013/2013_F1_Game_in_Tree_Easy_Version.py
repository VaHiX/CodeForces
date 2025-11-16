# Problem: CF 2013 F1 - Game in Tree (Easy Version)
# https://codeforces.com/contest/2013/problem/F1

"""
Algorithm/Techniques:
- Tree traversal using DFS to find parent relationships
- Path reconstruction from node u to node v
- Depth calculation for each node in the path
- Game theory analysis based on optimal move strategies
- Preprocessing of win/loss conditions for each position in the path

Time Complexity: O(n) for each test case, where n is the number of vertices
Space Complexity: O(n) for storing tree structure, parent relationships, and auxiliary arrays
"""

import os
import random
import sys
from collections import defaultdict
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
sys.setrecursionlimit(10000)
mag = random.getrandbits(20)


class D:
    def __init__(self, type=int):
        self.d = defaultdict(type)
        self.mag = random.getrandbits(20)

    def __setitem__(self, key, value):
        self.d[key + self.mag] = value

    def __getitem__(self, key):
        return self.d[key + self.mag]

    def __delitem__(self, key):
        del self.d[key + self.mag]

    def __contains__(self, key):
        return key + self.mag in self.d

    def __iter__(self):
        self.keys = iter(self.d.keys())
        return self

    def __next__(self):
        return next(self.keys) - self.mag

    def __len__(self):
        return len(self.d)


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
    u, v = mii()
    u -= 1
    par = [-1] * n
    st = [0]
    while st:
        x = st.pop()
        for y in d[x]:
            if y == par[x]:
                continue
            par[y] = x
            st.append(y)
    l = [u]
    while l[-1] != 0:
        l.append(par[l[-1]])
    depth = [0] * n
    par = [-1] * n
    dep = [0] * len(l)
    l.reverse()
    for i in range(len(l)):
        st = []
        max_depth = 0
        for y in d[l[i]]:
            if i > 0 and y == l[i - 1] or i < len(l) - 1 and y == l[i + 1]:
                continue
            st.append(y)
            depth[y] = 1
            max_depth = 1
            par[y] = l[i]
        while st:
            x = st.pop()
            for y in d[x]:
                if y == par[x]:
                    continue
                st.append(y)
                par[y] = x
                depth[y] = depth[x] + 1
                if depth[y] > max_depth:
                    max_depth = depth[y]
        dep[i] = max_depth
    bootA = [0] * len(l)
    bootB = [0] * len(l)
    for i in range(len(l)):
        bootA[i] = i + dep[i]
        bootB[i] = len(l) - i - 1 + dep[i]
    m = len(l)
    if m & 1:
        ba, bb = [], []
        for i in range(1, m // 2 + 1):
            ba.append(max(bootB[i], bootB[m - i]))
        ba.append(bootB[m // 2 + 1])
        for j in range(len(ba) - 2, -1, -1):
            ba[j] = max(ba[j], ba[j + 1])
        for i in range(1, m // 2 + 1):
            bb.append(max(bootA[i], bootA[m - i - 1]))
        for j in range(len(bb) - 2, -1, -1):
            bb[j] = max(bb[j], bb[j + 1])
        for i in range(m // 2):
            if bootA[i] > ba[i]:
                print("Alice")
                return
            if bootB[m - i - 1] >= bb[i]:
                print("Bob")
                return
        if bootA[m // 2] > bootB[m // 2 + 1]:
            print("Alice")
        else:
            print("Bob")
    else:
        ba, bb = [], []
        for i in range(1, m // 2 + 1):
            ba.append(max(bootB[i], bootB[m - i]))
        for j in range(len(ba) - 2, -1, -1):
            ba[j] = max(ba[j], ba[j + 1])
        for i in range(1, m // 2):
            bb.append(max(bootA[i], bootA[m - i - 1]))
        bb.append(bootA[m // 2 - 1])
        for j in range(len(bb) - 2, -1, -1):
            bb[j] = max(bb[j], bb[j + 1])
        for i in range(m // 2):
            if bootA[i] > ba[i]:
                print("Alice")
                return
            if bootB[m - i - 1] >= bb[i]:
                print("Bob")
                return


for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/CodeForces/