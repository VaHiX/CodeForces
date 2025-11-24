# Problem: CF 1283 E - New Year Parties
# https://codeforces.com/contest/1283/problem/E

"""
E. New Year Parties

Algorithm:
- The problem is about minimizing and maximizing the number of distinct houses occupied by friends after they move.
- Each friend can move to one of three positions: x_i - 1, x_i, or x_i + 1.
- To minimize occupied houses: Try to make as many friends occupy the same house.
- To maximize occupied houses: Try to ensure minimal overlap.

Approach:
1. Count how many friends are at each position.
2. For minimum occupied houses:
   - Greedily group friends together such that there's no gap (i.e., consecutive positions are filled).
   - Use a greedy method similar to interval merging, where we count the number of "gaps" in occupied positions.

3. For maximum occupied houses:
   - Maximize each friend's contribution to a distinct house.
   - Each friend can choose among 3 positions. The best way is to assign different positions where possible.

Time Complexity: O(n)
Space Complexity: O(n)
"""

import os
import sys
from io import BytesIO, IOBase

BUFSIZE = 4096


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


sys.stdin = IOWrapper(sys.stdin)
sys.stdout = IOWrapper(sys.stdout)
input = lambda: sys.stdin.readline().rstrip("\r\n")


def I():
    return input()


def II():
    return int(input())


def LII():
    return list(map(int, input().split()))


n = II()
a = LII()
cnt = [0] * (n + 1)
for v in a:
    cnt[v] += 1
prev_low, prev_up = -1, -1
low, up = 0, 0
for i, c in enumerate(cnt):
    if c > 0 and i > prev_low + 1:  # A gap is encountered, increment low count
        prev_low = i + 1
        low += 1
    if c > 0 and i > prev_up + 1:  # A gap is encountered for upper bound, increase up count
        prev_up = i - 1
        up += 1
        c -= 1
    if c > 0 and i == prev_up + 1:  # Same as above but for exact match condition
        prev_up = i
        up += 1
        c -= 1
    if c > 0 and i == prev_up:  # Special case to update previous upper bound
        prev_up = i + 1
        up += 1
print(low, up)


# https://github.com/VaHiX/codeForces/