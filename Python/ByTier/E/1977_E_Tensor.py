# Problem: CF 1977 E - Tensor
# https://codeforces.com/contest/1977/problem/E

"""
Interactive problem to color a directed graph with constraints.
Algorithm: 
- Use a greedy approach to assign colors to vertices
- First, find a "breakpoint" where a vertex cannot reach the next one
- Then process vertices sequentially, assigning colors based on reachability
- For each group of consecutive vertices that are reachable from each other, assign same color
Time Complexity: O(n^2) in worst case due to queries (but bounded by 2*n queries)
Space Complexity: O(n) for storing the coloring array
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


def I():
    return input()


def II():
    return int(input())


def MI():
    return map(int, input().split())


def LI():
    return list(input().split())


def LII():
    return list(map(int, input().split()))


def GMI():
    return map(lambda x: int(x) - 1, input().split())


inf = float("inf")


def ask(i, j):
    print("?", i + 1, j + 1, flush=True)
    return I() == "YES"


def answer(A):
    print("!", end=" ")
    print(*A, flush=True)


def solve(testcase):
    n = II()
    A = [0 for _ in range(n)]

    x, y = -1, -1

    # Find first pair where j cannot reach i+1
    for i in range(n - 1):
        if not ask(i, i + 1):
            A[i + 1] = 1
            x, y = i, i + 1
            break

    # If no such pair, all vertices can reach each other - color all black
    if x == -1:
        answer([0 for _ in range(n)])
        return

    # Process the rest of the vertices from position y onwards
    i = y + 1
    while i < n:
        # if y cannot reach i, then i needs to be colored same as x
        if not ask(y, i):
            A[i] = A[x]
            x = i
            i += 1
            continue

        # if x cannot reach i, then i needs to be colored same as y
        if not ask(x, i):
            A[i] = A[y]
            y = i
            i += 1
            continue

        # Find maximal consecutive sequence starting at i where each vertex can reach next one
        j = i + 1
        while j < n and ask(j - 1, j):
            j += 1

        # If we reached the end, break
        if j == n:
            break

        # Determine which color to assign to j and to all vertices between i and j-1
        if ask(x, j):
            # assign same color to j as x, and all previous vertices in range to color of y
            A[j] = A[x]
            for k in range(i, j):
                A[k] = A[y]
        else:
            # assign same color to j as y, and all previous vertices in range to color of x
            A[j] = A[y]
            for k in range(i, j):
                A[k] = A[x]

        # update x,y to new breakpoint
        x = j - 1
        y = j
        i = j + 1

    answer(A)


for testcase in range(II()):
    solve(testcase)


# https://github.com/VaHiX/CodeForces/