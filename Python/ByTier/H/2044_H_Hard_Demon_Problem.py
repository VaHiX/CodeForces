# Problem: CF 2044 H - Hard Demon Problem
# https://codeforces.com/contest/2044/problem/H

"""
Problem: Hard Demon Problem
Algorithm: 2D Range Sum with Weighted Sum using 2D Prefix Sums
Time Complexity: O(n^2 + q) per test case
Space Complexity: O(n^2) per test case

This solution uses 2D prefix sums to efficiently compute the weighted sum of elements in a submatrix.
We precompute three prefix sums:
- p1: regular prefix sum
- p2: prefix sum weighted by row index
- p3: prefix sum weighted by column index

For each query, we calculate the required weighted sum using inclusion-exclusion principle on these prefix sums.
"""

import os
import sys
from collections import *
from heapq import *
from io import BytesIO, IOBase
from math import gcd
from random import getrandbits
from types import GeneratorType

input = lambda: sys.stdin.readline().rstrip("\r\n")
flush = lambda: sys.stdout.flush()
print = (
    lambda *args, **kwargs: sys.stdout.write(
        " ".join(map(str, args)) + kwargs.get("end", "\n")
    )
    and flush()
)

sys.setrecursionlimit(100000)


def bootstrap(f, stack=[]):
    def wrappedfunc(*args, **kwargs):
        if stack:
            return f(*args, **kwargs)
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


def ints():
    return map(int, input().split())


def strs():
    return input().split()


def chars():
    return list(input().strip())


def mat(n):
    return [list(ints()) for _ in range(n)]


INF = float("inf")
MOD = 1000000007
abcd = "abcdefghijklmnopqrstuvwxyz"


def add(x, y, mod=MOD):
    return (x + y) % mod


def sub(x, y, mod=MOD):
    return (x - y) % mod


def mul(x, y, mod=MOD):
    return (x * y) % mod


def invmod(a, mod=MOD):
    return powmod(a, mod - 2, mod)


def lcm(a, b):
    return a * b // gcd(a, b)


RANDOM = getrandbits(32)


class Wrapper(int):
    def __init__(self, x):
        int.__init__(x)

    def __hash__(self):
        return super(Wrapper, self).__hash__() ^ RANDOM


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


def main():
    t = int(input())
    for _ in range(t):
        n, q = ints()
        mx = [list(ints()) for i in range(n)]
        # Initialize 3D prefix sum arrays
        p1 = [[0] * (n + 1) for _ in range(n + 1)]
        p2 = [[0] * (n + 1) for _ in range(n + 1)]
        p3 = [[0] * (n + 1) for _ in range(n + 1)]
        ans = []
        # Build prefix sums
        for i in range(1, n + 1):
            for j in range(1, n + 1):
                val = mx[i - 1][j - 1]
                # Regular prefix sum
                p1[i][j] = p1[i - 1][j] + p1[i][j - 1] - p1[i - 1][j - 1] + val
                # Prefix sum weighted by row index
                p2[i][j] = p2[i - 1][j] + p2[i][j - 1] - p2[i - 1][j - 1] + val * i
                # Prefix sum weighted by column index
                p3[i][j] = p3[i - 1][j] + p3[i][j - 1] - p3[i - 1][j - 1] + val * j
        # Process queries
        for _ in range(q):
            x1, y1, x2, y2 = ints()
            # Calculate sum of elements in submatrix using inclusion-exclusion
            prefix_r1 = (
                p1[x2][y2] - p1[x1 - 1][y2] - p1[x2][y1 - 1] + p1[x1 - 1][y1 - 1]
            )
            prefix_r2 = (
                p2[x2][y2] - p2[x1 - 1][y2] - p2[x2][y1 - 1] + p2[x1 - 1][y1 - 1]
            )
            prefix_r3 = (
                p3[x2][y2] - p3[x1 - 1][y2] - p3[x2][y1 - 1] + p3[x1 - 1][y1 - 1]
            )
            # Calculate weighted sum using derived formula
            ans.append(
                (y2 - y1 + 1) * (prefix_r2 - x1 * prefix_r1)
                + prefix_r3
                - y1 * prefix_r1
                + prefix_r1
            )
        print(*ans)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/