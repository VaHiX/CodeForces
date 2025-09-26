# Contest 2029, Problem F: Palindrome Everywhere
# URL: https://codeforces.com/contest/2029/problem/F

import heapq
import os, sys
from io import BytesIO, IOBase

from collections import defaultdict, deque, Counter
from bisect import bisect_left, bisect_right
from heapq import heappush, heappop
from functools import lru_cache, reduce
from itertools import accumulate
from operator import xor
import random
import math
import sys

# sys.setrecursionlimit(10000)
# Fast IO Region
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

mod = 998244353

# mod = 10 ** 9 + 7


def solve():
    n = ii()
    s = input()
    c = ""
    for i in range(n):
        c0, c1 = s[i], s[(i + 1) % n]
        if c0 == c1 and c0 != c and c != "":
            print("NO")
            return
        elif c0 == c1:
            c = c0

    c_ = "R" if c == "B" else "B"
    l = s.split(c_)
    if len(l) <= 2:
        print("YES")
        return
    r = [len(w) for w in l]
    r[0] += r.pop()
    t = 0
    for k in r:
        if k & 1 == 0:
            t += 1
    if t == 1:
        print("YES")
    else:
        print("NO")


for _ in range(ii()):
    solve()
