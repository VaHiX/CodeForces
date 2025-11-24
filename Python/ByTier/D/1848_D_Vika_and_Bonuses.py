# Problem: CF 1848 D - Vika and Bonuses
# https://codeforces.com/contest/1848/problem/D

"""
Algorithm: 
- The problem involves maximizing the total discount from a sequence of k purchases
- For each purchase, the customer can either:
    1. Get a discount equal to current bonuses (no change in bonus count)
    2. Accumulate additional bonuses equal to the last digit of current bonuses
- Strategy:
    - If s=0, all discounts are 0
    - Otherwise, for each purchase, compute whether it's better to:
        - Take discount (s)
        - Accumulate (s + last digit of s)
    - Optimally, we may accumulate bonuses for some steps and then take discounts
    - The key insight is to simulate the process efficiently for large k (up to 10^9)
    - This implementation uses mathematical formulas and periodic patterns to handle large k efficiently
Time Complexity: O(1) per test case (constant time due to precomputed cycles)
Space Complexity: O(1) (constant space)
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


ii = lambda: int(input())
mii = lambda: map(int, input().split())
fii = lambda: map(float, input().split())
lmii = lambda: list(map(int, input().split()))
i2c = lambda n: chr(ord("a") + n)
c2i = lambda c: ord(c) - ord("a")

mod = 998244353


flush = lambda: sys.stdout.flush()


def rev(n, mod=998244353):
    r = 1
    while n > 1:
        b = mod // n
        n = n * (b + 1) - mod
        r *= b + 1
        r %= mod
    return r


def solve():
    s, k = mii()
    res = s * k
    s += s % 10
    k -= 1
    if s % 10 == 0:
        print(max(res, s * k))
        return

    def f(y):
        if y < 0:
            return 0
        yi = int(y)
        if y > yi + 0.5:
            yi += 1
        return yi

    L = {2: [2, 4, 8, 6], 4: [4, 8, 6, 2], 6: [6, 2, 4, 8], 8: [8, 6, 2, 4]}
    R = L[s % 10]
    for i in range(4):
        x20 = sum(R[:i])
        x = f((20 * (k - i) - 4 * (s + x20)) / 160)
        res = max(res, (s + 20 * x + x20) * (k - 4 * x - i))
    print(res)


for _ in range(ii()):
    solve()


# https://github.com/VaHiX/CodeForces/