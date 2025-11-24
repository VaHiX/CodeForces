# Problem: CF 1738 G - Anti-Increasing Addicts
# https://codeforces.com/contest/1738/problem/G

"""
Algorithm: Anti-Increasing Addicts
Approach:
    This problem is about deleting exactly (n-k+1)^2 cells from an n x n grid such that there is no strictly increasing sequence of k cells.
    A strictly increasing sequence means that for k cells (x1,y1), (x2,y2), ..., (xk,yk), we have xi < x_{i+1} and yi < y_{i+1} for all i.
    
    Key idea:
        We need to avoid creating any strictly increasing path of length k.
        A greedy approach works: we try to delete cells in a way that prevents such increasing paths.
        We process columns from right to left and attempt to place forbidden cells in strategic locations.
        
    Time Complexity: O(n^2) per test case (amortized)
    Space Complexity: O(n^2) for storing grid and auxiliary arrays

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
    n, K = map(int, input().split())
    S = [list(input()) for _ in range(n)]
    A = [[] for _ in range(n)] # For each column, store rows that can be deleted
    for i in range(n - 1, -1, -1):  # Process from bottom to top
        for j in range(n):
            if S[i][j] == "0":
                A[j].append(i)

    used = [[False] * n for _ in range(n)] # Mark which cells are used for deletion
    add = n - K + 2 # Number of cells to mark in each column
    cc = 0 # Count of cells marked for deletion
    for j in range(K - 1): # For K-1 columns
        x = n - 1 # Start at bottom row
        for i in range(j, j + add): # Check 'add' columns starting from column j
            if not A[i] or A[i][-1] > x: # If no cell available to delete from this column, or the top of the list is above x
                nx = x # No more cells can be used in current column
            else:
                nx = A[i][-1] # Get the row number to remove
                while A[i] and A[i][-1] <= x: # Remove all rows from column i which are <= current x
                    A[i].pop()
            nx = min(nx, n - 1 - (K - 2 - j)) # Limit the new row number based on constraints
            if i == j + add - 1: # If at last column in this iteration
                nx = 0

            for k in range(nx, x + 1): # Mark cells for deletion in range [nx, x]
                if used[k][i]:
                    print("NO")
                    return
                used[k][i] = True
                cc += 1
            x = nx # Move x to new position

    # Check if all columns have been processed
    for i in range(n):
        if A[i]: # If any column still has cells to delete, fail
            print("NO")
            return

    ans = [[1] * n for _ in range(n)] # Initialize result grid with all 1s (not deleted)
    c = (n - K + 1) ** 2 # Required number of deletions
    assert c + cc == n**2 # Ensure total number consistency
    for i in range(n):
        for j in range(n):
            if used[i][j]:
                continue # Skip already marked cells
            if S[i][j] == "1": # If cell can be deleted
                c -= 1
                ans[i][j] = 0 # Mark as deleted
            else: # If cell cannot be deleted but has to be deleted
                print("NO")
                return

    if c != 0: # If we did not delete exactly (n- K + 1)^2 cells
        print("NO")
    else:
        print("YES")
        for row in ans:
            print(*row, sep="")


for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/CodeForces/