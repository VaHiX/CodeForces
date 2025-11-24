# Problem: CF 2003 E2 - Turtle and Inversions (Hard Version)
# https://codeforces.com/contest/2003/problem/E2

"""
Algorithm: 
This code solves the problem of finding the maximum number of inversions in an interesting permutation.
An interesting permutation satisfies certain conditions based on intervals and max/min values within those intervals.
The algorithm uses a greedy approach:
1. Process intervals to determine which positions belong to "0" or "1" sections (based on max/min constraints)
2. Calculate the maximum number of inversions considering the constraints

Time Complexity: O(n + m) where n is permutation length and m is number of intervals
Space Complexity: O(n) for storing intervals and notes array

Approach:
- For each position, determine if it belongs to a "0" or "1" section based on interval constraints
- Count inversions considering how elements in "0" sections can form inversions with "1" sections
- Adjust for boundary conditions and check for impossibility
"""

standard_input, packages, output_together = 1, 1, 0
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

t = II()
outs = []
for _ in range(t):
    n, m = MII()
    intervals = [[] for _ in range(n)]

    for _ in range(m):
        l, r = GMI()
        intervals[l].append(r)

    l = r = -1
    tl = tr = -1

    ans = 0
    notes = [-1] * n

    for x in range(n):
        # When we move past the current interval range
        if r < x and l != -1:
            # Check if interval constraints are valid
            if tr <= tl:
                ans = -1
                break
            # Mark the sections appropriately
            for i in range(l, tl + 1):
                notes[i] = 0
            for i in range(tr, r + 1):
                notes[i] = 1
            l = r = -1
            tl = tr = -1

        # Process all intervals starting at position x
        for y in intervals[x]:
            # First interval at this position
            if l == -1:
                l, r = x, y
                tl, tr = x, y
            else:
                # Extend the range with the new interval
                r = fmax(r, y)
                tl = x
                tr = fmin(tr, y)

    # Handle the last interval
    if l != -1:
        if tr <= tl:
            ans = -1
        else:
            for i in range(l, tl + 1):
                notes[i] = 0
            for i in range(tr, r + 1):
                notes[i] = 1

    if ans != -1:
        # Count how many elements are in section 1
        cnt1 = 0
        for num in notes:
            if num == 1:
                cnt1 += 1
            else:
                ans += cnt1

        # Additional inversions calculation
        cnt0 = n - cnt1
        ans += cnt1 * (cnt1 - 1) // 2 + cnt0 * (cnt0 - 1) // 2
        cur = ans

        cur0 = 0
        cur1 = 0

        # Recalculate inversions considering variable assignment
        for i in range(n):
            if notes[i] == -1:
                cur -= cur1
                cur += cnt1
                cnt1 += 1
                cnt0 -= 1
                cur += cnt0 - cur0
                cur -= cnt0
                if cur > ans:
                    ans = cur

            if notes[i]:
                cur1 += 1
            else:
                cur0 += 1

    outs.append(ans)

print("\n".join(map(str, outs)))


# https://github.com/VaHiX/CodeForces/