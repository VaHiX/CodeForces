# Problem: CF 2029 F - Palindrome Everywhere
# https://codeforces.com/contest/2029/problem/F

# ==============================================================================
# Problem: F. Palindrome Everywhere
# Purpose: Determine if every pair of vertices in a cyclic graph has a palindrome route
# Algorithm/Techniques:
#   - Graph traversal and palindrome route checking on cycles
#   - Analyze edge colors to determine route validity
# Time Complexity: O(n) per test case
# Space Complexity: O(n) for storing input string and intermediate results
# ==============================================================================

import os
import random
import sys
from collections import defaultdict
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
sys.setrecursionlimit(10000)
mag = random.getrandbits(20)


class D:
    def __init__(self, type=int):
        self.d = defaultdict(type)
        self.mag = random.getrandbits(20)

    def __setitem__(self, key, value):
        self.d[key + self.mag] = value

    def __getitem__(self, key):
        return self.d[key + self.mag]

    def __delitem__(self, key):
        del self.d[key + self.mag]

    def __contains__(self, key):
        return key + self.mag in self.d

    def __iter__(self):
        self.keys = iter(self.d.keys())
        return self

    def __next__(self):
        return next(self.keys) - self.mag

    def __len__(self):
        return len(self.d)


ii = lambda: int(input())
mii = lambda: map(int, input().split())
fii = lambda: map(float, input().split())
lmii = lambda: list(map(int, input().split()))
i2c = lambda n: chr(ord("a") + n)
c2i = lambda c: ord(c) - ord("a")
mod = 998244353


def solve():
    n = ii()
    s = input()
    c = ""  # Store the single color if all edges are same
    for i in range(n):
        c0, c1 = s[i], s[(i + 1) % n]  # Get current and next edge colors
        if c0 == c1 and c0 != c and c != "":
            print("NO")
            return
        elif c0 == c1:
            c = c0  # If both are same, store the color

    c_ = "R" if c == "B" else "B"  # Take the other color
    l = s.split(c_)  # Split by occurrence of c_
    if len(l) <= 2:  # If at most one segment of c_ exists, solution is YES
        print("YES")
        return

    r = [len(w) for w in l]  # Get lengths of segments
    r[0] += r.pop()  # Connect the first and last to form a cycle
    t = 0  # Count even-length segments
    for k in r:
        if k & 1 == 0:  # If even length
            t += 1
    if t == 1:  # Exactly one even-length segment means YES
        print("YES")
    else:
        print("NO")


for _ in range(ii()):
    solve()


# https://github.com/VaHiX/codeForces/