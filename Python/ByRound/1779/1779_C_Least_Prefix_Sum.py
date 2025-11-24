# Problem: CF 1779 C - Least Prefix Sum
# https://codeforces.com/contest/1779/problem/C

"""
Algorithm: Greedy with Heap
Time Complexity: O(n * log(n))
Space Complexity: O(n)

The problem asks us to minimize the prefix sum at index m, such that it becomes 
the smallest among all prefix sums. We can achieve this by flipping signs of elements 
in a way that reduces the value of prefix sums beyond index m and before index m.

Approach:
1. First, process elements from index m to n (inclusive). If an element is negative,
   push it into a min-heap. As we accumulate the sum from right to left, if the sum
   becomes negative, we flip the smallest negative element (from heap) to reduce
   the total sum.

2. Then, process elements from index m-1 down to 1 (inclusive). For this part, 
   we accumulate sum from right to left, but this time if sum becomes negative
   and there are positive elements in heap to flip, we do so.

We use a min-heap to efficiently get the smallest element to flip.

Key Insight:
We flip elements optimally to reduce negative prefix sums, ensuring at the end
that prefix sum at m is minimal among all.
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


def inpv():
    return int(input())


def inplt():
    return list(map(int, input().split()))


def insr():
    s = input()
    return list(s[: len(s)])


def invr():
    return map(int, input().split())


from collections import *
from heapq import *

tt = inpv()
for jjk in range(tt):
    n, m = inplt()
    A = inplt()
    ans = 0
    B = []
    a = 0
    # Process suffix elements from index m to n
    for i in range(m, n):
        a += A[i]
        if A[i] < 0:
            heappush(B, A[i])

        if a < 0:

            x = heappop(B)
            ans += 1
            a -= 2 * x
    B = []
    a = 0

    # Process prefix elements from index m-1 down to 1
    for i in range(m - 1, 0, -1):
        a += -1 * A[i]
        if A[i] > 0:
            heappush(B, -1 * A[i])

        if a < 0:

            x = heappop(B)
            ans += 1
            a -= 2 * x
    print(ans)


# https://github.com/VaHiX/CodeForces/