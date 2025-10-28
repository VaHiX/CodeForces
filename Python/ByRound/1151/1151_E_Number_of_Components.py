# Problem: CF 1151 E - Number of Components
# https://codeforces.com/contest/1151/problem/E

"""
E. Number of Components
Algorithms/Techniques: Slight optimization over brute force using monotonicity and incremental calculation.

Time Complexity: O(n)
Space Complexity: O(n)

The problem asks to compute the sum of f(l, r) over all pairs l <= r,
where f(l, r) is the number of connected components in a subgraph induced
by vertices with values in [l, r]. Since the graph is a tree on a path,
connected components are just contiguous segments.

Instead of recalculating f(l,r) for each pair, we can compute contribution
of each element to the final answer efficiently using a two-pointer approach
or by observing how the number of components changes when we expand the range.
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


def solve():
    n = int(input())
    A = list(map(int, input().split()))
    # Base case contribution from first element
    ans = (n - A[0] + 1) * (A[0])
    for i, a in enumerate(A):
        if i == 0:
            continue
        b = A[i - 1]
        # When we extend range to include current value 'a'
        # If a >= b: we gain components from values between b and a
        # If a < b: we lose components due to gap between a and b
        if a >= b:
            ans += (n - a + 1) * (a - b)
        else:
            ans += (b - a) * (a)
    print(ans)


for _ in range(1):
    solve()


# https://github.com/VaHiX/codeForces/