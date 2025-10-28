# Problem: CF 2001 E1 - Deterministic Heap (Easy Version)
# https://codeforces.com/contest/2001/problem/E1

"""
Algorithm: Dynamic Programming with Prefix Sums and Modular Arithmetic
Time Complexity: O(n * k^2)
Space Complexity: O(n * k)

This solution counts the number of deterministic max-heaps that can be formed
by performing exactly k "add" operations on a perfect binary tree of height n.
Each operation adds 1 to all nodes on the path from root to a chosen node.

Key techniques used:
1. Dynamic Programming: dp[i][j] represents number of ways to form valid heaps
   at height i with exactly j operations.
2. Prefix Sums: Efficient computation of sums in the recurrence relation.
3. Modular Arithmetic: All operations done modulo p for large numbers.
4. Inverse Elements: Precomputed modular inverses for division in modular arithmetic.

The algorithm uses the recurrence relation based on how operations are distributed
across subtree levels, with careful handling of the deterministic heap constraint.
"""

import os
import sys
from io import BytesIO, IOBase


def main():
    t = int(input())
    for _ in range(t):
        n, k, p = map(int, input().split())
        # Precompute modular inverses for later use
        inv = [-1] + [pow(i, -1, p) for i in range(1, k + 1)]
        # dp[i][j] = number of ways to get exactly j operations at height i
        dp = [[0] * (k + 1) for _ in range(n + 1)]
        # Base case: at height 1, we can only have 0 operations (empty heap) or any number of operations
        dp[1] = [1] * (k + 1)
        dp[1][0] = 0  # We must perform at least one operation, so dp[1][0] is 0
        for i in range(2, n + 1):
            # pref[x] = sum of choose from 0 to x (prefix sum)
            pref, choose, child_sz = [0] * k, 1, (pow(2, i - 1, p) - 1) % p
            # Compute prefix sums for combinations using recurrence
            for x in range(k):
                pref[x] = (pref[x - 1] + choose) % p
                choose = (choose * (child_sz + x) * inv[x + 1]) % p
            for j in range(1, k + 1):
                # For each possible split of operations at current level
                for hi in range(1, j + 1):
                    lo = min(hi - 1, j - hi)
                    # Add to the result the contribution from current split
                    dp[i][j] = (dp[i][j] + 2 * pref[lo] * dp[i - 1][hi]) % p
        print(dp[n][k])


BUFSIZE = 8192


class FastIO(IOBase):
    newlines = 0

    def __init__(self, file):
        self._file = file
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
if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/