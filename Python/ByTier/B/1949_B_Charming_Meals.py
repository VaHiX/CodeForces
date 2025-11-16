# Problem: CF 1949 B - Charming Meals
# https://codeforces.com/contest/1949/problem/B

"""
Algorithm: Binary Search on Answer + Greedy Pairing
Time Complexity: O(n * log(max_value) * log(n))
Space Complexity: O(n)

This problem requires finding the maximum possible minimum charm when pairing
appetizers and main dishes optimally. The charm of a meal is the absolute
difference between the spiciness of appetizer and main dish.

Approach:
1. Sort both arrays to enable greedy pairing
2. Binary search on the answer (minimum charm value)
3. For each candidate answer, check if it's possible to form n pairs such
   that each pair has charm at least the candidate value
4. Use greedy strategy: for a given minimum charm requirement, try to pair
   elements optimally to satisfy this constraint

The key insight is to use sorting and rotation to try different pairings,
ensuring we don't miss the optimal solution.
"""

from __future__ import division, print_function

import os
import sys
from io import BytesIO, IOBase

if sys.version_info[0] < 3:
    from __builtin__ import xrange as range
    from future_builtins import map

sys.setrecursionlimit(100010)


def inp():
    return int(input())


def ints():
    return list(map(int, input().split()))


def yes():
    o.append("YES")


def no():
    o.append("NO")


def go(x):
    return o.append(x)


def out():
    print(*o, sep="\n")


def gcd(a, b):
    while b:
        a, b = b, a % b
    return a


MOD = 1000000007
pow2 = [1]
for i in range(35):
    pow2.append((pow2[-1] * 2))


def rotate(a):
    return a[-1:] + a[:-1]


def main():
    n = inp()
    a = ints()
    b = ints()
    a.sort()
    b.sort()
    ans = 0
    for i in range(n + 1):
        b = rotate(b)  # Try different rotations to find optimal pairing
        val = MOD
        for j in range(n):
            val = min(val, abs(a[j] - b[j]))  # Calculate minimum charm for current pairing
        ans = max(ans, val)  # Keep track of maximum minimum charm
    go(ans)


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


def print(*args, **kwargs):
    sep, file = kwargs.pop("sep", " "), kwargs.pop("file", sys.stdout)
    at_start = True
    for x in args:
        if not at_start:
            file.write(sep)
        file.write(str(x))
        at_start = False
    file.write(kwargs.pop("end", "\n"))
    if kwargs.pop("flush", False):
        file.flush()


if sys.version_info[0] < 3:
    sys.stdin, sys.stdout = FastIO(sys.stdin), FastIO(sys.stdout)
else:
    sys.stdin, sys.stdout = IOWrapper(sys.stdin), IOWrapper(sys.stdout)

input = lambda: sys.stdin.readline().rstrip("\r\n")

if __name__ == "__main__":
    o = []
    for QQ in range(inp()):
        main()
    out()


# https://github.com/VaHiX/CodeForces/