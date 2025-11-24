# Problem: CF 1866 J - Jackets and Packets
# https://codeforces.com/contest/1866/problem/J

"""
Algorithm: Dynamic Programming with State Compression
Time Complexity: O(N^3) where N is the number of jackets
Space Complexity: O(N^2) for the DP table

The problem involves packing jackets into packets with same colors using two types of operations:
1. Move one jacket from one stack to another (cost Y)
2. Pack multiple jackets of same color from top of a stack (cost X)

We use a 3D DP state where:
- dp[0][f(l, r)] represents the minimum cost to pack jackets from l to r (both ends inclusive)
- dp[1][f(l, r)] represents the minimum cost to pack jackets from l to r where the leftmost jacket is moved
- dp[2][f(l, r)] represents the minimum cost to pack jackets from l to r where the rightmost jacket is moved

The solution builds on intervals and considers how to split them optimally, along with movement operations between stacks.
"""

standard_input, packages, output_together = 1, 1, 0
dfs, hashing, read_from_file = 0, 0, 0
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
            return input().split()

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

        def bootstrap(f, stk=[]):
            def wrappedfunc(*args, **kwargs):
                if stk:
                    return f(*args, **kwargs)
                else:
                    to = f(*args, **kwargs)
                    while True:
                        if type(to) is GeneratorType:
                            stk.append(to)
                            to = next(to)
                        else:
                            stk.pop()
                            if not stk:
                                break
                            to = stk[-1].send(to)
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

    class lst_lst:
        def __init__(self, n) -> None:
            self.n = n
            self.pre = []
            self.cur = []
            self.notest = [-1] * (n + 1)

        def append(self, i, j):
            self.pre.append(self.notest[i])
            self.notest[i] = len(self.cur)
            self.cur.append(j)

        def iterate(self, i):
            tmp = self.notest[i]
            while tmp != -1:
                yield self.cur[tmp]
                tmp = self.pre[tmp]


n, x, y = MII()
nums = [0] + LII()  # 1-indexed array


def f(i, j):
    return i * (n + 1) + j  # Map 2D coordinates to 1D index


inf = 10**15  # Large value for infinity
# Initialize DP table: dp[0][f(l, r)] minimum cost from l to r
dp = [[inf] * ((n + 1) * (n + 1)) for _ in range(3)]
for i in range(1, n + 1):
    for j in range(3):
        dp[j][f(i, i - 1)] = 0  # Base case: empty interval
    dp[0][f(i, i)] = x  # Base case: single jacket needs packing cost X

# Precompute cost of packing from l to r directly (without movement)
for i in range(1, n + 1):
    cur = x
    for j in range(i + 1, n + 1):
        if nums[j] != nums[j - 1]:
            cur += x  # if adjacent elements differ, we need more packs
        dp[0][f(i, j)] = cur

# Dynamic Programming on intervals
for step in range(n):  # step represents the length of the interval minus 1
    for l in range(1, n - step + 1):  # l is left endpoint
        r = l + step  # r is right endpoint
        # Try all possible splits of the interval [l, r]
        for sep in range(l, r):
            dp[0][f(l, r)] = fmin(dp[0][f(l, r)], dp[0][f(l, sep)] + dp[0][f(sep + 1, r)])
        
        # If we can move the jackets to the same state and merge them
        if step and nums[l] == nums[r]:
            # Case 1: Moving the leftmost jacket (state 1)
            dp[1][f(l, r)] = dp[0][f(l + 1, r - 1)] + 2 * y  # move l to right stack and r to left stack
            # Case 2: Moving both leftmost and rightmost jackets (state 2)
            dp[2][f(l, r)] = dp[0][f(l + 1, r - 1)] + 4 * y  # move l to right stack, r to left stack

            # Explore further splits that involve moving a jacket to match nums[l] with nums[sep]
            for sep in range(l + 1, r):
                if nums[l] == nums[sep]:  # when we can combine with other elements
                    # Update with moving elements such that the prefix is combined with the prefix and suffix is treated separately
                    dp[1][f(l, r)] = fmin(dp[1][f(l, r)], dp[1][f(l, sep)] + dp[0][f(sep + 1, r - 1)] + y)
                    dp[2][f(l, r)] = fmin(dp[2][f(l, r)], dp[2][f(l, sep)] + dp[0][f(sep + 1, r - 1)] + 2 * y)
            
            # Combine the best move into the final result (for packing)
            dp[0][f(l, r)] = fmin(dp[0][f(l, r)], dp[1][f(l, r)] + x)
            
            # Handle suffix combinations to optimize cost
            for sep in range(r, l - 1, -1):  # backward scan from r to l
                if nums[sep] != nums[r]:
                    break  # stop if not compatible
                dp[0][f(l, r)] = fmin(dp[0][f(l, r)], dp[2][f(l, sep)] - 2 * y + x)

# The required answer is the minimum cost to process all jackets from 1 to n
print(dp[0][f(1, n)])


# https://github.com/VaHiX/CodeForces/