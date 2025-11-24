# Problem: CF 1777 D - Score of a Tree
# https://codeforces.com/contest/1777/problem/D

"""
Algorithm: Tree Processing with Layer Assignment
Time Complexity: O(n) per test case
Space Complexity: O(n) per test case

This problem involves computing the sum of F(A) across all 2^n possible initial configurations of a tree.
F(A) is the sum of S(t) over all t from 0 to 10^100, where S(t) is the sum of values at time t.
The key insight is that after some time, all internal nodes will have value 0 due to XOR operations.
The tree is processed layer by layer (from leaves to root), and we compute how many times each node contributes
to the total sum. The contribution of each node is proportional to its layer in the tree.
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


from collections import deque

MOD_NUM = 10**9 + 7


def solve():
    n = int(input())
    G = [[] for _ in range(n)]
    for _ in range(n - 1):
        u, v = map(int, input().split())
        u -= 1
        v -= 1

        G[u].append(v)
        G[v].append(u)

    # ctr[u] counts number of children for node u
    ctr = [0] * n
    vis = [False] * n
    par = [-1] * n
    stk = [0]
    q = deque()
    while stk:
        u = stk[-1]
        if not vis[u]:
            vis[u] = True
            for v in G[u]:
                if not vis[v]:
                    par[v] = u
                    stk.append(v)
        else:
            stk.pop()
            for v in G[u]:
                if v != par[u]:
                    ctr[u] += 1

            if ctr[u] == 0:
                q.append(u)

    # layer[u] assigns a layer number to each node, higher = further from root
    layer = [1] * n
    while q:
        u = q.popleft()

        p = par[u]
        ctr[p] -= 1
        if ctr[p] == 0:
            layer[p] = layer[u] + 1
            q.append(p)

    # Total contribution is sum(layer) * 2^(n-1)
    ans = sum(layer) * pow(2, n - 1, MOD_NUM) % MOD_NUM
    print(ans)


for nt in range(int(input())):
    solve()


# https://github.com/VaHiX/CodeForces/