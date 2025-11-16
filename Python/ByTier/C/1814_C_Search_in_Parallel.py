# Problem: CF 1814 C - Search in Parallel
# https://codeforces.com/contest/1814/problem/C

"""
Algorithm: Greedy Assignment
Time Complexity: O(n log n) - due to sorting
Space Complexity: O(n) - for storing the lists and the sorted enumerated requests

This problem involves assigning boxes (colors) to two robots such that the total search time for all requests is minimized.
We use a greedy strategy: 
1. Sort the colors by their request frequency in descending order.
2. Assign each color to the robot that currently has the least total time spent (to balance load).
3. The first robot gets assigned colors to its list 'robot1', and the second to 'robot2'.

The key insight is that when we have a high-frequency request, we want to assign it to the robot that will be able to process it faster in terms of accumulated time,
to minimize the total time spent across all requests.
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


def print(*values, sep=" ", end="\n", flush=False):
    sys.stdout.write(sep.join(map(str, values)) + end)
    if flush:
        sys.stdout.flush()


t = int(input())
for _ in range(t):
    n, s1, s2 = [int(i) for i in input().split()]
    r = [int(i) for i in input().split()]

    dtr1, dtr2 = s1, s2  # Current total time for robot1 and robot2
    robot1, robot2 = [], []
    # Sort by request frequency in descending order to prioritize high-frequency colors
    for b, _ in sorted(enumerate(r), reverse=True, key=lambda x: x[1]):
        # Assign to the robot with less accumulated time to balance load
        if dtr1 < dtr2:
            robot1.append(b + 1)
            dtr1 += s1  # Update the time spent
        else:
            robot2.append(b + 1)
            dtr2 += s2

    print(len(robot1), " ".join(map(str, robot1)))
    print(len(robot2), " ".join(map(str, robot2)))


# https://github.com/VaHiX/CodeForces/