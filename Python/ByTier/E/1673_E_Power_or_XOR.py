# Problem: CF 1673 E - Power or XOR?
# https://codeforces.com/contest/1673/problem/E

"""
Algorithm: Dynamic Programming with Bit Manipulation
Time Complexity: O(n^2 * log(max(B_i)) + 2^20)
Space Complexity: O(2^20)

The problem involves evaluating all possible combinations of power and XOR operations 
on a sequence of numbers A_i = 2^B_i, where each operator can be either power (^) or XOR (⊕). 
We are interested in the XOR of all valid results that use at least k operators as XOR operations.

Key insight:
1. Since A_i = 2^B_i, we can work directly with exponents for power operations.
2. For any subsequence from index i to j, we compute its power result as 2^(sum of B_i's multiplied by powers).
3. We use a dynamic programming approach to track which exponent values can result from valid XOR combinations.
4. For each valid configuration (using at least k XORs), we update the answer using XOR.

The check function determines if a particular segment can be used as XOR in a valid expression.
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


BUFSIZE = 4096


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


def checkOdd(x, y):
    return x == (x - y) | y


def check(l, r):
    a = max(l - 1, 0) + max(n - 2 - r, 0)
    b = k
    if l:
        b -= 1
    if r < n - 1:
        b -= 1
    b = max(0, b)
    if b == 0:
        return a == 0
    if b > a:
        return False
    return checkOdd(a - 1, b - 1)


n, k = MII()
nums = LII()
mod = 2**20
note = [0] * mod
for i in range(n):
    tmp = nums[i]
    if check(i, i):
        note[tmp] ^= 1
    for j in range(i + 1, n):
        if nums[j] > 20:
            break
        tmp *= 1 << nums[j]
        if tmp >= mod:
            break
        if check(i, j):
            note[tmp] ^= 1
while note[-1] == 0 and len(note) > 1:
    note.pop()
note.reverse()
print(*note, sep="")


# https://github.com/VaHiX/CodeForces/