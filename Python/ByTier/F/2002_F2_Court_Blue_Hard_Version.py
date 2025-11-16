# Problem: CF 2002 F2 - Court Blue (Hard Version)
# https://codeforces.com/contest/2002/problem/F2

"""
F2. Court Blue (Hard Version)

This problem is about finding the maximum score a performance can achieve under specific constraints regarding GCD and win counts.

Key Techniques:
- Dynamic Programming with memoization
- Mathematical GCD properties to determine valid states
- Optimization using bounded iteration space

Time Complexity: O(n * m) per test case, where n and m are the limits on wins for Lelle and Flamm respectively.
Space Complexity: O(n * m) for the dp array used to track valid states.

Approach:
We iterate through potential win counts for both players, and use a DP table to determine if a state (i,j) where i is Lelle's wins and j is Flamm's wins is valid. A state is valid if:
1. gcd(i, j) <= 1
2. We can reach it from previous valid states by either increasing Lelle's or Flamm's wins.

We track maximum score attainable at each valid state.
"""

standard_input, packages, output_together = 1, 0, 0
dfs, hashing, read_from_file = 1, 0, 0
de = 1
if 1:
    if standard_input:
        import os
        import sys

        input = lambda: sys.stdin.readline().strip()
        import math

        inf = math.inf

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

        def LFI():
            return list(map(float, input().split()))

        def GMI():
            return map(lambda x: int(x) - 1, input().split())

        def LGMI():
            return list(map(lambda x: int(x) - 1, input().split()))

    if packages:
        import os
        import random
        from io import BytesIO, IOBase

        BUFSIZE = 4096
    if output_together:

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

        sys.stdout = IOWrapper(sys.stdout)
    if dfs:
        from types import GeneratorType

        def bootstrap(f, stack=[]):
            def wrappedfunc(*args, **kwargs):
                if stack:
                    return f(*args, **kwargs)
                else:
                    to = f(*args, **kwargs)
                    while True:
                        if type(to) is GeneratorType:
                            stack.append(to)
                            to = next(to)
                        else:
                            stack.pop()
                            if not stack:
                                break
                            to = stack[-1].send(to)
                    return to

            return wrappedfunc

    if hashing:
        RANDOM = random.getrandbits(20)

        class Wrapper(int):
            def __init__(self, x):
                int.__init__(x)

            def __hash__(self):
                return super(Wrapper, self).__hash__() ^ RANDOM

    if read_from_file:
        file = open("input.txt", "r").readline().strip()[1:-1]
        fin = open(file, "r")
        input = lambda: fin.readline().strip()
        output_file = open("output.txt", "w")

        def fprint(*args, **kwargs):
            print(*args, **kwargs, file=output_file)

    if de:

        def debug(*args, **kwargs):
            print("\033[92m", end="")
            print(*args, **kwargs)
            print("\033[0m", end="")

    fmax = lambda x, y: x if x > y else y
    fmin = lambda x, y: x if x < y else y
bound = 55
dp = [0] * (bound * bound)


def p(x, y):
    return x * bound + y


for i in range(bound):
    dp[p(i, 0)] = dp[p(0, i)] = 1   # Initialize base cases: start with (0,j) and (i,0) being valid states
t = II()
outs = []
for _ in range(t):
    x, y, v1, v2 = MII()            # Read n, m, l, f for current test case
    sx = fmax(x - 53, 0)            # Calculate starting x coordinate
    sy = fmax(y - 53, 0)            # Calculate starting y coordinate
    ans = 0                         # Initialize max score
    for i in range(1, x - sx + 1):  # Iterate over rows (Lelle's wins)
        for j in range(1, y - sy + 1):  # Iterate over columns (Flamm's wins)
            if math.gcd(sx + i, sy + j) == 1 and (dp[p(i - 1, j)] or dp[p(i, j - 1)]):  # Check GCD and reachability
                dp[p(i, j)] = 1
                ans = fmax(ans, v1 * (sx + i) + v2 * (sy + j))   # Update maximum score if valid
            else:
                dp[p(i, j)] = 0    # Mark invalid state
    outs.append(ans)
print("\n".join(map(str, outs)))


# https://github.com/VaHiX/codeForces/