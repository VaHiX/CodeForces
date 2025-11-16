# Problem: CF 1500 B - Two chandeliers
# https://codeforces.com/contest/1500/problem/B

"""
Algorithm: Binary search with inclusion-exclusion principle
Time Complexity: O(n * log(max(n,m)) + log(5*10^17))
Space Complexity: O(n + max(n,m))

The problem involves two cyclic chandeliers with different color sequences.
We need to find the day when they differ for the k-th time.

Key insight:
- The chandeliers repeat their colors every lcm(n,m) days
- We compute all valid positions where the chandeliers have same color in one cycle
- Using binary search, we check how many differing days exist up to a certain point
- The inclusion-exclusion technique helps count overlapping cycles correctly

Approach:
1. Precompute positions of colors in second chandelier for fast lookup
2. Find all indices where colors match in one cycle using extended GCD
3. Use binary search to find the day when k-th difference occurs
"""

import math
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


def ext_gcd(a, b):
    if b == 0:
        return a, 1, 0
    gcd, x, y = ext_gcd(b, a % b)
    return gcd, y, x - (a // b) * y


def mod_inv(a, p):
    gcd, x, y = ext_gcd(a, p)
    return x % p


n, m, tot = MII()

nums1 = LII()
nums2 = LII()

pos = [None] * (2 * max(n, m) + 1)
for i, v in enumerate(nums2):
    pos[v] = i

gcd = math.gcd(n, m)
inv = mod_inv(n // gcd, m // gcd)
lcm = math.lcm(n, m)

sols = [None] * n
for i in range(n):
    j = pos[nums1[i]]

    if j is None or (i - j) % gcd:
        continue
    k = (j - i) // gcd * inv % (m // gcd)
    sols[i] = (k * n + i) % lcm + 1

l, r = 1, 5 * 10**17
while l <= r:
    mid = (l + r) // 2
    res = mid
    for i in range(n):
        if sols[i] is not None:
            res -= (mid - sols[i]) // lcm + 1
    if res >= tot:
        r = mid - 1
    else:
        l = mid + 1
print(l)


# https://github.com/VaHiX/CodeForces/