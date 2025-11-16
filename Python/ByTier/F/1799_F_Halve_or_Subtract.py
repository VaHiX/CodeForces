# Problem: CF 1799 F - Halve or Subtract
# https://codeforces.com/contest/1799/problem/F

"""
Algorithm: Dynamic Programming with Preprocessing
Time Complexity: O(n^2) per test case
Space Complexity: O(n) per test case

The problem involves minimizing the sum of an array after applying two types of operations:
1. Halve an element (floor division by 2)
2. Subtract b from an element (but not less than 0)

We use preprocessing to compute cumulative sums and optimal values for different combinations of operations.

Key ideas:
- Sort array in descending order to prioritize larger elements for operations
- Precompute f[i]: sum of gains from halving first i elements (after subtracting b)
- Precompute g[i]: sum of halved values of first i elements
- Precompute h[i]: sum of gains from subtracting b from first i elements
- Use nested loops to iterate over all valid combinations of operations
- Calculate final cost using prefix sums and cumulative arrays
"""

import os
import sys
from io import BytesIO, IOBase
from itertools import accumulate

BUFSIZE = 4096


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


t = II()
for _ in range(t):
    n, b, op1, op2 = MII()
    nums = LII()
    nums.sort(reverse=True)
    acc = list(accumulate(nums, initial=0))

    f = [0] * 5001
    g = [0] * 5001
    h = [0] * 5001
    for i in range(n):
        f[i + 1] = f[i] + max(0, (nums[i] + 1) // 2 - b)  # Sum of gains from halving (with offset)
        g[i + 1] = g[i] + (nums[i] + 1) // 2               # Sum of halved values
        h[i + 1] = h[i] + max(0, nums[i] - b)              # Sum of gains from subtraction

    ans = inf
    for i in range(n + 1):  # i = number of operations of type 1 on first i elements
        for j in range(n + 1):  # j = number of operations of type 2 on first j elements
            if op1 >= i + j and op2 >= i and op1 + op2 - i <= n:
                # Calculate cost for this combination of operations
                ans = min(
                    ans,
                    f[i]                           # Gain from halving first i elements
                    + g[i + j]                     # Sum of halved values for first i+j elements
                    - g[i]                         # Subtract halving for first i elements (to prevent double counting)
                    + h[op2 + j]                   # Gain from subtracting b for first op2+j elements
                    - h[i + j]                     # Subtract subtracting for first i+j elements (to prevent double counting)
                    + g[op1 + op2 - i]             # Extra halving that would be done if we did op1+op2-i operations total
                    - g[op2 + j]                   # Subtract the extra halving that we already counted
                    + acc[n]                       # Total sum of original array
                    - acc[op1 + op2 - i],         # Subtract the portion that is not modified
                )
    print(ans)


# https://github.com/VaHiX/CodeForces/