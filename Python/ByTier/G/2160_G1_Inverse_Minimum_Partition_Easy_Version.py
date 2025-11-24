# Problem: CF 2160 G1 - Inverse Minimum Partition (Easy Version)
# https://codeforces.com/contest/2160/problem/G1

"""
Algorithm: Convex Hull Trick + Dynamic Programming
Time Complexity: O(n log n) per test case
Space Complexity: O(n)

This solution uses dynamic programming with convex hull trick to find the minimum cost partition
of a sequence. The key insight is that for each element, we need to decide whether to start a new
segment or continue the current one, which leads to a DP formulation. The convex hull trick helps
optimize the DP transition by maintaining a set of lines and querying the minimum value efficiently.

The 'cost' of a sequence is defined as ceil(k / min_element) where k is the length of sequence.
We use a convex hull trick to maintain the optimal DP transitions and minimize the total cost.
"""

import os
import sys
from io import BytesIO, IOBase

_str = str
str = lambda x=b"": x if type(x) is bytes else _str(x).encode()

BUFSIZE = 8192


class FastIO(IOBase):
    newlines = 0

    def __init__(self, file):
        self._file = file
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


class ConvexHullTrick:
    def __init__(self, minimize=True):
        self.deq = deque()
        self.minimize = minimize

    def is_bad(self, l1, l2, l3):
        # Check if line l2 is redundant between l1 and l3
        return (l3[1] - l1[1]) * (l1[0] - l2[0]) <= (l2[1] - l1[1]) * (l1[0] - l3[0])

    def add(self, m, b):
        # Add line (m, b) to the deque maintaining convex hull property
        while len(self.deq) >= 2 and self.is_bad(self.deq[-2], self.deq[-1], (m, b)):
            self.deq.pop()
        self.deq.append((m, b))

    def f(self, line, x):
        # Evaluate line at x
        return line[0] * x + line[1]

    def query(self, x):
        # Query minimum value of lines at x
        while len(self.deq) >= 2 and self.f(self.deq[0], x) >= self.f(self.deq[1], x):
            self.deq.popleft()
        return self.f(self.deq[0], x)


import math

t = int(input())
for _ in range(t):
    n = int(input())
    l = list(map(int, input().split()))
    a = [(l[i], i) for i in range(n)]
    a = sorted(a, key=lambda x: (x[0], x[-1]))
    p = -1
    newl = []
    for v, i in a:
        if i > p:
            newl.append(v)
            p = i
    n = len(newl)
    l = newl
    inv = []
    for i in l:
        inv.append(1 / i)
    dp = [float("inf")] * n
    cht = ConvexHullTrick(min)
    dp[0] = 1
    cht.add(inv[0], 0)
    for i in range(1, n):
        # Transition: either start a new segment (cost 1 + dp[i-1]) or continue (query from convex hull)
        dp[i] = min(1 + dp[i - 1], math.ceil(cht.query(l[i])))
        cht.add(inv[i], dp[i - 1])
    print(dp[-1])


# https://github.com/VaHiX/CodeForces/