# Problem: CF 1733 E - Conveyor
# https://codeforces.com/contest/1733/problem/E

"""
Algorithm: Conveyor Slime Ball Movement Simulation
Approach: 
- Model the movement of slime balls through a conveyor belt system with direction changes
- Use dynamic programming to track the number of slime balls at each position
- Simulate the process using a counting approach and then trace the final path

Time Complexity: O(120 * 120) per query = O(1) since grid size is fixed
Space Complexity: O(120 * 120) = O(1) since grid size is fixed

This solution tracks how slime balls move through time using a propagation method,
then traces the actual path of one particular slime ball to determine if it reaches
the target position.
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


def solve():
    t, x, y = map(int, input().split())
    # Calculate distance from origin (0,0) to target (x,y)
    d = x + y
    # If distance is greater than time, slime cannot reach the position
    if d > t:
        print("NO")
        return
    # Update time to remaining time after reaching (x,y) through optimal path
    t -= d
    # Create a 2D array to count slime balls at each position
    cnt = [[0] * 120 for _ in range(120)]
    # Initially place t slime balls at position (0,0)
    cnt[0][0] = t
    # Propagate slime balls through conveyor system
    # For each cell in the grid, distribute slime to adjacent cells
    for i in range(120):
        for j in range(120):
            # Move half of the slime balls down (if not at bottom)
            if i != 119:
                cnt[i + 1][j] += cnt[i][j] // 2
            # Move half of the slime balls right (if not at rightmost)
            if j != 119:
                cnt[i][j + 1] += (cnt[i][j] + 1) // 2

    # Trace the path of one slime ball backwards to determine if it reaches (x,y)
    i = j = 0
    # Follow d steps that were already accounted for
    for _ in range(d):
        # If there's an odd number of slime balls at current position,
        # path goes down; otherwise, path goes right
        if cnt[i][j] & 1:
            i += 1
        else:
            j += 1
        # If out of bounds, no solution exists
        if i == 120 or j == 120:
            print("NO")
            return
    # Check if final position matches target position
    if i == x and j == y:
        print("YES")
    else:
        print("NO")


for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/CodeForces/