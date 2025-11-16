# Problem: CF 1977 D - XORificator
# https://codeforces.com/contest/1977/problem/D

"""
Algorithm: XORificator
Purpose: Given a binary n×m matrix, determine the maximum number of columns that can be made "special" (exactly one 1) by choosing which rows to XOR (invert all values in that row). 
Technique: 
- Use randomization with XOR to reduce problem to counting similar XOR patterns
- For each column, compute XOR of row indices where that column has a 1
- Use this as a hash to count how many columns match a certain XOR pattern (same pattern implies same result after row flips)
- Find the best row/column pair to use for flipping

Time Complexity: O(n * m), since we process each element once in the main loop
Space Complexity: O(n + m), for storing the matrix and auxiliary data structures
"""

import os
import sys
from io import BytesIO, IOBase
from random import getrandbits

from _collections import defaultdict

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

    rd = []
    for i in range(N):   # Generate random bits for each row to use in hashing
        rd.append(getrandbits(63))

    mp = defaultdict(int)  # Map to count occurrences of XOR patterns

    mx = 0  # Maximum special columns achievable
    ref = (-1, -1)  # Best row and column indices to flip to achieve max
    for j in range(M):  # For each column
        x = 0  # XOR of row indices with 1s in current column
        for i in range(N):
            if A[i][j] == 1:
                x ^= rd[i]

        # Try flipping each row and count how many columns would be special
        for i in range(N):
            x ^= rd[i]  # Flip the bit at index i (simulate XOR operation)
            mp[x] += 1  # Count how many columns match this pattern
            if mp[x] > mx:  # Update best match if current is better
                mx = mp[x]
                ref = (i, j)
            x ^= rd[i]  # Undo the change

    res = []
    for i in range(N):
        # Determine if we need to flip this row based on best solution
        res.append(A[i][ref[1]] ^ (i == ref[0]))

    return str(mx) + "\n" + "".join(str(v) for v in res)


for test in range(1, ui() + 1):
    N, M = mi()
    A = [lsi() for _ in range(N)]

    print(solve())

file.close()


# https://github.com/VaHiX/CodeForces/