# Problem: CF 2162 G - Beautiful Tree
# https://codeforces.com/contest/2162/problem/G

"""
Beautiful Tree Construction

This code constructs a tree with n vertices such that the sum of products of vertex labels for all edges is a perfect square.
The algorithm uses specific patterns for different values of n:
- For n=2, no beautiful tree exists, so we return -1
- For n=3, we construct a star graph with center vertex 3
- For n=4, we construct a specific tree with edges (4,2), (2,3), (2,1)
- For n>=5, we build a linear chain and connect remaining vertices to vertex 2

Time Complexity: O(n) - We process each vertex once to print edges
Space Complexity: O(1) - We only use a constant amount of extra space

Algorithms/Techniques:
- Greedy construction with specific patterns
- Tree edge generation based on n values
"""

import os
import sys
from io import BytesIO, IOBase


def solve(case):
    n = int(input())
    if n == 2:
        print(-1)
        return
    if n == 3:
        print(2, 3)
        print(3, 1)
        return
    if n == 4:
        print(4, 2)
        print(2, 3)
        print(2, 1)
        return

    # For n >= 5, construct a tree:
    # Start with a path: 1-2-3-4
    print(1, 2)
    print(2, 3)
    print(3, 4)
    # Connect all remaining vertices to vertex 2
    for i in range(5, n):
        print(2, i)
    # Connect vertex 1 to vertex n to form a valid tree
    print(1, n)


def main():
    t = 1
    for _ in range(int(input()) if t else 1):
        solve(case=_ + 1)


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