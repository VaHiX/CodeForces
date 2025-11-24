# Problem: CF 1698 F - Equal Reversal
# https://codeforces.com/contest/1698/problem/F

"""
Algorithm: Equal Reversal
Techniques: Greedy, Simulation, Sorting, Two Pointers
Time Complexity: O(n^3) in worst case due to nested loops for finding and performing operations
Space Complexity: O(n^2) for storing counter maps and operations list

This solution works by:
1. First checking if transformation is possible by comparing sorted pairs of adjacent elements
2. If possible, it simulates the transformation by finding positions where elements differ
3. For each mismatch, it finds the corresponding element and performs reversals to fix it
4. Uses a greedy approach to minimize unnecessary operations while maintaining correctness
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
        from collections import Counter
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
            self.lst = [-1] * n

        def append(self, i, j):
            self.pre.append(self.lst[i])
            self.lst[i] = len(self.cur)
            self.cur.append(j)

        def iterate(self, i):
            tmp = self.lst[i]
            while tmp != -1:
                yield self.cur[tmp]
                tmp = self.pre[tmp]


t = II()
outs = []

for _ in range(t):
    n = II()
    nums1 = LII()
    nums2 = LII()

    cnt1 = Counter()
    cnt2 = Counter()

    # Count adjacent pairs in original array
    for i in range(1, n):
        x, y = nums1[i], nums1[i - 1]
        if x > y:
            x, y = y, x
        cnt1[(x, y)] += 1

    # Count adjacent pairs in target array
    for i in range(1, n):
        x, y = nums2[i], nums2[i - 1]
        if x > y:
            x, y = y, x
        cnt2[(x, y)] += 1

    # Check if transformation is possible
    if cnt1 != cnt2 or nums1[0] != nums2[0] or nums1[-1] != nums2[-1]:
        outs.append("NO")
    else:
        outs.append("YES")
        ops = []

        # Function to reverse elements in array from index l to r
        def operate(l, r):
            ops.append(f"{l +1 } {r +1 }")
            while l < r:
                nums1[l], nums1[r] = nums1[r], nums1[l]
                l += 1
                r -= 1

        # Main algorithm to transform nums1 into nums2
        for i in range(n):
            if nums1[i] != nums2[i]:
                # Get the pair we want to move element to
                x, y = nums2[i - 1], nums2[i]
                if x > y:
                    x, y = y, x

                # Find where the matching adjacent pair occurs
                for j in range(i, n):
                    vx, vy = nums1[j - 1], nums1[j]
                    if vx > vy:
                        vx, vy = vy, vx
                    if vx == x and vy == y:
                        # Check if we need to perform a swap
                        if nums1[j] != nums2[i - 1]:
                            # Find index of desired element and perform reversal
                            vis = {}
                            for idx in range(i - 1, j):
                                vis[nums1[idx]] = idx
                            for idx in range(j, n):
                                if nums1[idx] in vis:
                                    operate(vis[nums1[idx]], idx)
                                    break
                        else:
                            # Direct reversal from i-1 to j
                            operate(i - 1, j)
                        break

            # Check if element fixed
            if nums1[i] != nums2[i]:
                x, y = nums2[i - 1], nums2[i]
                if x > y:
                    x, y = y, x

                # Find correct adjacent pair again
                for j in range(i, n):
                    vx, vy = nums1[j - 1], nums1[j]
                    if vx > vy:
                        vx, vy = vy, vx
                    if vx == x and vy == y:
                        if nums1[j] == nums2[i - 1]:
                            operate(i - 1, j)
                            break

        outs.append(str(len(ops)))
        if len(ops):
            outs.append("\n".join(ops))

print("\n".join(outs))


# https://github.com/VaHiX/CodeForces/