# Problem: CF 1227 A - Math Problem
# https://codeforces.com/contest/1227/problem/A

"""
A. Math Problem
time limit per test
2 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output

Your math teacher gave you the following problem:
There are n segments on the x-axis, [l_1; r_1], [l_2; r_2], ..., [l_n; r_n]. The segment [l; r] includes the bounds, i.e. it is a set of such x that l <= x <= r. The length of the segment [l; r] is equal to r - l.
Two segments [a; b] and [c; d] have a common point (intersect) if there exists x that a <= x <= b and c <= x <= d. For example, [2; 5] and [3; 10] have a common point, but [5; 6] and [1; 4] don't have.
You should add one segment, which has at least one common point with each of the given segments and as short as possible (i.e. has minimal length). The required segment can degenerate to be a point (i.e a segment with length zero). The added segment may or may not be among the given n segments.
In other words, you need to find a segment [a; b], such that [a; b] and every [l_i; r_i] have a common point for each i, and b-a is minimal.

Algorithms/Techniques:
- Greedy approach to find the minimum length of a segment covering all given segments.
- The key insight is that we need to select a segment [a,b] such that it intersects with all given segments.
  The optimal choice is to pick a segment that starts at the maximum of all left bounds and ends at the minimum of all right bounds.
  If this interval is invalid (start > end), then we return 0.

Time Complexity: O(n) for each test case, where n is the number of segments.
Space Complexity: O(n) for storing the segment data.

"""

import math
import os
import sys
from io import BytesIO, IOBase


def lcm(a, b):
    return (a * b) // math.gcd(a, b)


def main():
    t = int(input())
    for _ in range(t):
        n = int(input())
        i = 0
        d = []  # Store left bounds of segments
        k = []  # Store right bounds of segments
        while i < n:
            l, r = map(int, input().split())
            d.append(l)
            k.append(r)
            i += 1
        # The minimum segment that covers all given segments starts at max(d) and ends at min(k)
        # The length is max(0, min(k) - max(d)) since we want non-negative length
        print(max(max(d) - min(k), 0))


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


# https://github.com/VaHiX/codeForces/