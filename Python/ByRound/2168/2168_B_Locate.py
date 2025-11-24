# Problem: CF 2168 B - Locate
# https://codeforces.com/contest/2168/problem/B

"""
Problem: Locate
Algorithm/Technique: Binary search, interactive problem solving
Time Complexity: O(n log n) for first run, O(log n) for second run
Space Complexity: O(n) for storing the permutation

This is a run-twice (communication) interactive problem where:
- Player A (first run) receives the full permutation and sends a binary value x to jury
- Player B (second run) receives only n and x, then uses at most 30 queries to find
  the position of integer n in the permutation

Strategy:
- First run (Player A): 
  - Determine x = 0 if the position of 1 is less than position of n
  - Otherwise, x = 1
- Second run (Player B):
  - Use binary search to locate n's position
  - When x = 0: search for the leftmost position where query(0, pos) == n-1
  - When x = 1: search for the rightmost position where query(pos, n) != n-1

The difference between max and min in a subarray gives us information about the range
in that subarray. When we know n's position, we can use this to deduce its location
by checking subarrays containing or not containing n.
"""

import os
import sys
from io import BytesIO, IOBase


def discrete_binary_search(func, lo, hi):
    """Locate the first value x s.t. func(x) = True within [lo, hi]"""
    while lo < hi:
        mi = lo + (hi - lo) // 2
        if func(mi):
            hi = mi
        else:
            lo = mi + 1

    return lo


def main():
    def query(l, r):
        print("?", l + 1, r, flush=True)
        resp = int(input())
        assert resp != -1
        return resp

    run = input()

    if run == "first":
        # First run - Player A
        t = int(input())
        for _ in range(t):
            n = int(input())
            # Convert to 0-based indexing for easier handling
            p = [int(pi) - 1 for pi in input().split()]
            # Send x = 0 if position of 1 (0-indexed) is less than position of n (n-1-indexed)
            # Otherwise send x = 1
            print(0 if p.index(0) < p.index(n - 1) else 1)
    else:
        # Second run - Player B
        t = int(input())
        for _ in range(t):
            n, x = map(int, input().split())

            if x == 0:
                # If x = 0, then position of 1 is less than position of n
                # We want to find the leftmost position such that range [0, pos] contains n
                # and has range (n-1). So we are looking for first such position.
                print(
                    "!",
                    discrete_binary_search(lambda x: query(0, x) == n - 1, 2, n),
                    flush=True,
                )
            else:
                # If x = 1, then position of 1 is greater than or equal to position of n
                # We look for a position such that range [pos, n] does not contain n
                # This means the range is not n-1, so n must be to the left of pos
                print(
                    "!",
                    discrete_binary_search(lambda x: query(x, n) != n - 1, 1, n - 1),
                    flush=True,
                )


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