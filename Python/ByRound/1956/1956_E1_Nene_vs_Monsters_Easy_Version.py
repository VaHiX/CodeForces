# Problem: CF 1956 E1 - Nene vs. Monsters (Easy Version)
# https://codeforces.com/contest/1956/problem/E1

"""
Algorithm: Simulation with Optimization
Time Complexity: O(n) amortized, where n is the number of monsters
Space Complexity: O(n) for storing the array

The problem simulates a process where monsters attack their neighbors in a circle, 
and we need to find which monsters remain after 10^100 rounds. 

Key insights:
- After many rounds, the system reaches a stable state where only certain monsters 
  can possibly have non-zero energy
- The simulation can be optimized by detecting cycles and using mathematical 
  formulas to compute the final state without simulating all 10^100 rounds
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


if sys.version_info[0] < 3:
    sys.stdin = BytesIO(os.read(0, os.fstat(0).st_size))
else:
    sys.stdin, sys.stdout = IOWrapper(sys.stdin), IOWrapper(sys.stdout)
file = sys.stdin
if os.environ.get("USER") == "loic":
    file = open("data.in")
line = lambda: file.readline().split()
ui = lambda: int(line()[0])
mi = lambda: map(int, line())
li = lambda: list(mi())
lsi = lambda: list(map(int, line()[0]))


def solve():
    arr = A.copy()
    stop = False
    # First simulation to determine a stable pattern
    while not stop:
        for i in range(1, N + 1):
            arr[i % N] = max(arr[i % N] - arr[i - 1], 0)
        c = 0
        stop = True
        # Check if the pattern has stabilized (less than 4 non-zero elements)
        for i in range(N + 4):
            if arr[i % N] != 0:
                c += 1
                if c > 3:
                    stop = False
                    break
            else:
                c = 0
    st = -1
    # Second simulation to identify the starting point of the stable pattern
    for i in range(1, N + 1):
        arr[i % N] = max(arr[i % N] - arr[i - 1], 0)
        if arr[i % N] == 0:
            st = i
            break
    c = 0
    # Apply mathematical reasoning to compute final state
    for i in range(st, st + N + 1):
        if arr[i % N] == 0:
            if c == 2:
                arr[(i - 1) % N] = 0
            elif c == 3:
                d = arr[(i - 3) % N]
                k = arr[(i - 2) % N] // d
                rem = arr[(i - 2) % N] % d
                s = rem * k + d * (k - 1) * k // 2
                if arr[(i - 1) % N] <= s:
                    arr[(i - 1) % N] = 0
                arr[(i - 2) % N] = 0
            c = 0
        else:
            c += 1
    # Collect indices of remaining non-zero monsters
    res = [i for i in range(N) if arr[i] != 0]
    return str(len(res)) + "\n" + " ".join(str(v + 1) for v in res)


for test in range(1, ui() + 1):
    N = ui()
    A = li()
    print(solve())
file.close()


# https://github.com/VaHiX/CodeForces/