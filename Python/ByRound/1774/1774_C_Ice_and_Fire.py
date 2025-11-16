# Problem: CF 1774 C - Ice and Fire
# https://codeforces.com/contest/1774/problem/C

"""
Algorithm: 
- For each x from 2 to n, determine how many players can potentially win the tournament.
- The key insight is to simulate the tournament by analyzing the binary string s and how it affects the outcome of battles.
- Players are initially sorted by their temperature values.
- For each x, we consider players with temperature values from 1 to x.
- The tournament proceeds by always choosing two players and fighting in an environment determined by string s.
- We use a greedy approach to compute which players can win: 
  - For each new player added, we check if the environment type changes.
  - If environment type changes, a new player can win; otherwise, the previous winner continues.
- Time Complexity: O(n), where n is the number of players.
- Space Complexity: O(n), for storing the answer array and processing the string.

Techniques:
- Simulation
- Greedy approach
- String handling
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


def input():
    return sys.stdin.readline().rstrip("\r\n")


_ = 1
_ = int(input())
while _ > 0:
    _ -= 1

    n = int(input())
    s = input()
    ans = [1]
    for i in range(1, n - 1):
        if s[i] == s[i - 1]:
            ans.append(ans[-1])
        else:
            ans.append(i + 1)
    print(*ans)


# https://github.com/VaHiX/CodeForces/