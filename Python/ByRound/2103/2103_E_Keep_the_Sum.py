# Contest 2103, Problem E: Keep the Sum
# URL: https://codeforces.com/contest/2103/problem/E

# Visit my repo: https://github.com/Yawn-Sean/Daily_CF_Problems
standard_input, packages, output_together = 1, 1, 0
dfs, hashing, read_from_file = 0, 0, 0
de = 1

if 1:

    if standard_input:
        import io, os, sys

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
        from io import BytesIO, IOBase

        import random
        import os

        import bisect
        import typing
        from collections import Counter, defaultdict, deque
        from copy import deepcopy
        from functools import cmp_to_key, lru_cache, reduce
        from heapq import (
            merge,
            heapify,
            heappop,
            heappush,
            heappushpop,
            nlargest,
            nsmallest,
        )
        from itertools import accumulate, combinations, permutations, count, product
        from operator import add, iand, ior, itemgetter, mul, xor
        from string import ascii_lowercase, ascii_uppercase, ascii_letters
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


t = II()
outs = []

rnd = random.getrandbits(30)

for _ in range(t):
    n, k = MII()
    nums = LII()

    if nums == sorted(nums):
        outs.append("0")
    else:
        # [a, ..., x, ..., k - x, ..., b]
        # [a, ..., a, ..., k - a, ..., b]
        # [k - b, ..., a, ..., b, ..., b]

        vis = Counter()
        l, r = -1, -1
        for i in range(n):
            target = (k - nums[i]) ^ rnd
            if target in vis:
                l, r = vis[target], i
                break
            vis[nums[i] ^ rnd] = i

        if l == -1:
            outs.append("-1")
        else:
            # [0, ..., x, ..., y, ..., k]
            # [x, ..., x, ..., y, ..., k - x]
            # [x, ..., y, ..., y, ..., k - y]
            # [x, ..., y, ..., x, ..., k - x]
            ops = []

            def op(x, y, diff_x):
                if x >= abs(diff_x):
                    ops.append(f"{x + 1} {y + 1} {-diff_x}")
                else:
                    ops.append(f"{y + 1} {x + 1} {diff_x}")
                nums[x] += diff_x
                nums[y] -= diff_x

            op(l, r, nums[0] - nums[l])
            op(0, r, k - nums[-1] - nums[0])

            target = [0] + sorted(range(1, n - 1), key=lambda x: nums[x]) + [n - 1]

            def swap(x, y):
                op(0, n - 1, nums[x] - nums[0])
                op(x, n - 1, nums[y] - nums[x])
                op(y, n - 1, nums[0] - nums[y])

            cur = list(range(n))
            pos = list(range(n))

            for i in range(n):
                if cur[i] != target[i]:
                    j = pos[target[i]]
                    swap(i, j)
                    cur[i], cur[j] = cur[j], cur[i]
                    pos[cur[i]], pos[cur[j]] = pos[cur[j]], pos[cur[i]]

            op(0, n - 1, -nums[0])
            outs.append(str(len(ops)))
            outs.append("\n".join(ops))

print("\n".join(outs))
