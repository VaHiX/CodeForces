# Problem: CF 1942 C1 - Bessie's Birthday Cake (Easy Version)
# https://codeforces.com/contest/1942/problem/C1

"""
Purpose: This code solves the problem of maximizing the number of non-intersecting triangular pieces
         that can be formed from a regular n-sided polygon by choosing vertices to form diagonals.
         The key insight is to count how many triangles can be formed by the given vertices,
         which is related to how many consecutive vertices are chosen and how many additional
         vertices can be added to maximize triangle count.

Algorithms/Techniques:
- Sorting the chosen vertices to analyze adjacency
- Iterating through sorted vertices to count gaps and consecutive segments
- Using the formula derived from geometric properties of triangulation

Time Complexity: O(x log x) due to sorting, where x is the number of chosen vertices.
Space Complexity: O(1) excluding input storage, as we only use a few variables to track counts.
"""

import os
import sys
from io import BytesIO, IOBase

sys.setrecursionlimit(100000)
INF = 10**18

MOD = 11400714819323198549


def power(x, y, p):
    res = 1
    x = x % p

    while y > 0:
        if y & 1:
            res = (res * x) % p
        y = y >> 1
        x = (x * x) % p
    return res


def modInverse(n, p):
    return power(n, p - 2, p)


def mul(x, y, p):
    return (x * y) % p


def divide(x, y, p):
    return mul(x, modInverse(y, p), p)


def nCrModPFermat(n, r, p):
    if n < r:
        return 0
    if r == 0:
        return 1
    if n - r < r:
        return nCrModPFermat(n, n - r, p)
    res = 1
    for i in range(1, r + 1):
        res = divide(mul(res, n - i + 1, p), i, p)
    return res


def modInverse(n):
    m = MOD
    s0 = 1
    t0 = 0
    s1 = 0
    t1 = 1
    while n % m:
        q = n // m
        r = n % m
        s = s0 - s1 * q
        t = t0 - t1 * q
        tmp = s1
        s1 = s
        s0 = tmp
        tmp = t1
        t1 = t
        t0 = tmp
        n, m = m, r

    return s1 % MOD


def non_intersecting_triangles(n, x):

    if x < 3 or x > n:
        return 0

    total_triangles = 0

    if x == 3:
        total_triangles += 1

    total_triangles += (x - 2) * (n - x + 1)

    return total_triangles


def main():
    for i in range(int(input())):
        n, x, y = map(int, input().split())
        arr = [int(x) for x in input().split()]
        arr.sort()
        vertex = x
        # Count additional vertices that can be added to form more triangles
        for j in range(x):
            # Check if two adjacent vertices in sorted array are exactly 2 apart (1 gap)
            if arr[(j + 1) % x] - arr[j] == 2:
                vertex += 1
            # Handle wraparound case: if last vertex is n and first is 1, it's a gap of 2
            if arr[(j + 1) % x] == 2 and arr[j] == n:
                vertex += 1
            elif arr[(j + 1) % x] == 1 and arr[j] == n - 1:
                vertex += 1
        # Return number of triangles from this vertex count
        print(vertex - 2)


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


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/