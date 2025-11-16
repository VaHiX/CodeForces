# Problem: CF 2163 C - Monopati
# https://codeforces.com/contest/2163/problem/C

"""
Algorithm: 
- The problem asks to count the number of pairs (l, r) such that there exists a down-right path 
  from (1,1) to (2,n) in the binary grid f(l,r), where f(l,r) has 1s in positions where l <= a[i][j] <= r.

- Key insight:
    - A down-right path from (1,1) to (2,n) must go through exactly n-1 right moves and 1 down move.
    - Each cell (i, j) in the path must be 1 in f(l,r).
    - f(l,r) is 1 at (i,j) iff l <= a[i][j] <= r.
    - For a valid path from (1,1) to (2,n), there exists a path that goes from (1,1) to (2,n) 
      where all cells in the path satisfy the condition l <= a[i][j] <= r.

- Solution approach:
    - Use coordinate compression or discrete values of matrix elements.
    - Preprocess for all possible values to check valid l,r pairs efficiently.
    - Use minimum and maximum prefix/suffix arrays to avoid checking all pairs individually.
    - A key observation: for any l,r, the path is valid if we can reach from (1,1) to (2,n) 
      in the binary grid where elements are in [l,r].
    - The algorithm computes min and max for each prefix and suffix and uses them to calculate 
      how many valid pairs (l,r) exist for each l.

Time Complexity: O(N)
Space Complexity: O(N)
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


if sys.version_info[0] < 3:
    sys.stdin = BytesIO(os.read(0, os.fstat(0).st_size))
else:
    sys.stdin, sys.stdout = IOWrapper(sys.stdin), IOWrapper(sys.stdout)

file = sys.stdin
if os.environ.get("USER") == "loic":
    file = open("data.in")

line = lambda: file.readline().split()
ui = lambda: int(line()[0])
mi = lambda: map(int, line())
li = lambda: list(mi())
lsi = lambda: list(map(int, line()[0]))


def solve():

    # Initialize arrays for min and max prefix/suffix computation
    mn_a = [0] * (N + 1)
    for i in range(N):
        if i == 0:
            mn_a[i] = A[i]
        else:
            mn_a[i] = min(mn_a[i - 1], A[i])
    mn_b = [0] * (N + 1)
    for i in range(N - 1, -1, -1):
        if i == N - 1:
            mn_b[i] = B[i]
        else:
            mn_b[i] = min(mn_b[i + 1], B[i])

    mx_a = [0] * (N + 1)
    for i in range(N):
        if i == 0:
            mx_a[i] = A[i]
        else:
            mx_a[i] = max(mx_a[i - 1], A[i])
    mx_b = [0] * (N + 1)
    for i in range(N - 1, -1, -1):
        if i == N - 1:
            mx_b[i] = B[i]
        else:
            mx_b[i] = max(mx_b[i + 1], B[i])

    # Compute minimum value for all valid ranges
    mn = [1 << 30] * (2 * N + 1)
    for i in range(N):
        cur_mn = min(mn_a[i], mn_b[i])
        cur_mx = max(mx_a[i], mx_b[i])
        mn[cur_mn] = min(mn[cur_mn], cur_mx)

    # Propagate minimum values forward
    for i in range(2 * N - 1, -1, -1):
        mn[i] = min(mn[i + 1], mn[i])

    res = 0
    for val in range(1, 2 * N + 1):
        if mn[val] != 1 << 30:
            res += 2 * N + 1 - mn[val]

    return str(res)


Z = 1 << 30

for test in range(1, ui() + 1):
    N = ui()
    A = li()
    B = li()

    print(solve())

file.close()


# https://github.com/VaHiX/CodeForces/