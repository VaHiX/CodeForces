# Problem: CF 1827 B2 - Range Sorting (Hard Version)
# https://codeforces.com/contest/1827/problem/B2

"""
Algorithm: Range Sorting (Hard Version)
Purpose: Calculate the sum of beauty over all subarrays of the given array.
Beauty of an array: Minimum time to sort using range-sort operations where each operation sorts a subarray in (r - l) seconds.

Time Complexity: O(n)
Space Complexity: O(n)

The solution uses:
1. Finding previous smaller elements for each index
2. Finding suffix smaller elements for each index
3. Using a stack-based approach to efficiently compute the contribution of each element to the final result
4. Mathematical formula to compute total sum minus invalid contributions
"""

standard_input, packages, output_together = 1, 1, 1
dfs, hashing, read_from_file = 0, 0, 0

if standard_input:
    import sys

    input = lambda: sys.stdin.readline().rstrip("\r\n")

    inf = float("inf")

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


def solve():
    n = II()
    nums = LII()

    # prev_smaller[i] = index of previous smaller element to the right of i
    prev_smaller = [-1] * n
    stack = []
    for i in range(n - 1, -1, -1):
        while stack and nums[stack[-1]] >= nums[i]:
            prev_smaller[stack.pop()] = i
        stack.append(i)

    # suff_smaller[i] = index of next smaller element to the left of i
    suff_smaller = [n] * n
    stack = []
    for i in range(n):
        while stack and nums[stack[-1]] >= nums[i]:
            suff_smaller[stack.pop()] = i
        stack.append(i)

    # prev_smaller2[i] = index of previous smaller or equal element to the right of i (with different logic)
    prev_smaller2 = [-1] * n
    stack = []
    second = []
    for i in range(n - 1, -1, -1):
        while second and nums[i] > nums[second[-1]]:
            prev_smaller2[second.pop()] = i
        while stack and nums[i] < nums[stack[-1]]:
            second.append(stack.pop())
        stack.append(i)
    
    # Calculate contribution based on mathematical derivation
    # Total possible subarrays = n*(n+1)/2
    # Subtract invalid contributions computed from the arrays
    print(
        (n - 1) * n * (n + 1) // 6
        - sum(
            (prev_smaller[i] - prev_smaller2[i]) * (suff_smaller[i] - i)
            for i in range(n)
        )
    )
    return


t = II()
for _ in range(t):
    solve()


# https://github.com/VaHiX/CodeForces/