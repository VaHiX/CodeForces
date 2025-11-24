# Problem: CF 1856 D - More Wrong
# https://codeforces.com/contest/1856/problem/D

"""
Algorithm: Binary Search with Inversion Counting
Purpose: Find the index of the maximum element in a hidden permutation using queries about inversions in subarrays.
Time Complexity: O(n * log^2(n)) 
Space Complexity: O(n * log(n)) for memoization and recursion stack

The key idea:
1. Use binary search to locate the maximum element.
2. For a subarray [l, r], if we know the number of inversions in [l, r] and [l+1, r], 
   we can determine if l is the index of the maximum element.
3. If query(l,r) - query(l+1,r) == (r - l), it means all elements in [l+1, r] are greater than p[l].
   Therefore, p[l] is the maximum in [l, r].

This approach minimizes the number of queries by using binary search.
"""

import os
import sys
from io import BytesIO, IOBase


class IOWrapper(IOBase):
    def __init__(self, file):
        self.buffer = FastIO(file)
        self.flush = self.buffer.flush
        self.writable = self.buffer.writable
        self.write = lambda s: self.buffer.write(s.encode("ascii"))
        self.read = lambda: self.buffer.read().decode("ascii")
        self.readline = lambda: self.buffer.readline().decode("ascii")


BUFSIZE = 5096


class FastIO(IOBase):
    newlines = 0

    def __init__(self, file):
        self._fd = file.fileno()
        self.buffer = BytesIO()
        self.writable = "x" in file.mode or "r" not in file.mode
        self.write = self.buffer.write if self.writable else None

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

    def read(self):
        while True:
            b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
            if not b:
                break
            ptr = self.buffer.tell()
            self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
        self.newlines = 0
        return self.buffer.read()


sys.stdin = IOWrapper(sys.stdin)
sys.stdout = IOWrapper(sys.stdout)
input = lambda: sys.stdin.readline().rstrip("\r\n")


def I():
    return input()


def II():
    return int(input())


def MII():
    return map(int, input().split())


def LI():
    return list(input().split())


def LII():
    return list(map(int, input().split()))


def GMI():
    return map(lambda x: int(x) - 1, input().split())


def LGMI():
    return list(map(lambda x: int(x) - 1, input().split()))


inf = float("inf")


def query(x, y):
    # Memoization to avoid repeated queries
    if x == y:
        return 0
    if (x, y) in note:
        return note[(x, y)]
    print("?", x, y, flush=True)
    note[(x, y)] = II()
    return note[(x, y)]


def solve(l, r):
    # Base case: only one element
    if l == r:
        return l
    
    # Binary search step
    m = (l + r) // 2
    
    # Recursively find max in left half
    left = solve(l, m)
    
    # Check if left is actually the max in [l, r]
    # If all elements in [l+1, r] are greater than p[l], then p[l] is the max
    # This is determined by the difference: (inversions on [l,r] - inversions on [l+1,r])
    if query(left, r) - query(left + 1, r) == r - left:
        return left
    
    # If not, max must be in right half
    return solve(m + 1, r)


t = II()
for _ in range(t):
    n = II()
    note = {}
    print("!", solve(1, n), flush=True)


# https://github.com/VaHiX/CodeForces/