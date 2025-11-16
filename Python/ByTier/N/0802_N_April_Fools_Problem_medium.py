# Problem: CF 802 N - April Fools' Problem (medium)
# https://codeforces.com/contest/802/problem/N

"""
Algorithm: Min Cost Flow / Binary Search + Greedy
Time Complexity: O(n * log(max_val) * log(n)) where max_val is the range of costs
Space Complexity: O(n)

This problem involves selecting k problems to prepare and print optimally over n days.
Each problem has a preparation cost and a printing cost.
We must ensure that a problem is prepared before it's printed.
This is modeled as a min cost flow problem where we:
- Binary search on the answer (the cost threshold)
- For each threshold, decide how to assign preparation and printing days
- The greedy assignment uses two heaps to maintain optimal selection
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
        from heapq import heappop, heappush
        from io import BytesIO, IOBase
        from typing import *

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
        file = open("input.txt", "r")
        input = file.readline
        def I(): return input().rstrip()
        def MII(): return map(int, input().split())
        def LII(): return list(map(int, input().split()))

    if de:
        def debug(*args, sep="", end="\n"):
            print(*args, sep=sep, end=end, file=sys.stderr)

n, k = MII()
nums1 = LII()
nums2 = LII()

l, r = -(10**10), 10**10
while l <= r:
    m = (l + r) // 2

    tot = cnt = 0
    hpq1 = []
    hpq2 = []

    for i in range(n):
        heappush(hpq1, nums1[i] - m)
        if hpq2 and (
            (hpq2[0] + nums2[i] < 0 and hpq2[0] < hpq1[0])
            or (hpq1[0] + nums2[i] > 0 and -hpq2[0] > nums2[i])
        ):
            heappop(hpq2)
            heappush(hpq2, -nums2[i])
        elif hpq1[0] + nums2[i] < 0:
            cnt += 1
            heappop(hpq1)
            heappush(hpq2, -nums2[i])
    if cnt <= k:
        l = m + 1
    else:
        r = m - 1

tot = cnt = 0
hpq1 = []
hpq2 = []

for i in range(n):
    heappush(hpq1, nums1[i] - r)
    if hpq2 and (
        (hpq2[0] + nums2[i] < 0 and hpq2[0] < hpq1[0])
        or (hpq1[0] + nums2[i] > 0 and -hpq2[0] > nums2[i])
    ):
        tot += nums2[i] + heappop(hpq2)
        heappush(hpq2, -nums2[i])
    elif hpq1[0] + nums2[i] < 0:
        cnt += 1
        tot += heappop(hpq1) + nums2[i]
        heappush(hpq2, -nums2[i])

print(tot + r * k)


# https://github.com/VaHiX/CodeForces/