# Problem: CF 1974 G - Money Buys Less Happiness Now 
# https://codeforces.com/contest/1974/problem/G

"""
Algorithm: Greedy with Priority Queue (Max Heap)
Approach:
- Charlie earns 'x' pounds each month and can only spend money earned in later months.
- For each month i, we decide whether to buy happiness now or defer it.
- We use a max heap (min heap with negative values) to maintain the most expensive happiness we've bought so far.
- When we receive money in month i, we try to buy happiness in month i+1.
- If we can't afford it, we consider swapping with the most expensive happiness previously bought (if cheaper).
Time Complexity: O(m * log(m)) due to heap operations across m months.
Space Complexity: O(m) for the heap storing at most m elements.
"""
import os
import sys
from bisect import *
from collections import *
from functools import *
from heapq import *
from io import BytesIO, IOBase
from itertools import *
from math import *
from operator import *
from types import *

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


def sol(m, x, c):
    pq = []  # Max heap to store costs of happiness bought so far (negative values)
    cur = 0  # Total money accumulated so far
    for i in range(1, m):  # From month 1 to m-1 (0-indexed), since we buy in next month
        cur += x  # Earn salary for current month
        if cur >= c[i]:  # If we can afford happiness in next month
            cur -= c[i]  # Spend money on happiness
            heappush(pq, -c[i])  # Add to heap (negative for max heap behavior)
        elif pq and -pq[0] > c[i]:  # If we have previously bought happiness and its cost is greater than current
            cur += -heappop(pq) - c[i]  # Replace previous expensive happiness with current cheaper one
            heappush(pq, -c[i])
    return len(pq)  # Return number of units of happiness


t = int(input().strip())
for q in range(t):
    m, x = list(map(int, input().strip().split()))
    c = list(map(int, input().strip().split()))
    print(sol(m, x, c))


# https://github.com/VaHiX/CodeForces/