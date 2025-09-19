# Contest 1089, Problem A: Alice the Fan
# URL: https://codeforces.com/contest/1089/problem/A

standard_input, packages, output_together = 1, 1, 0
dfs, hashing, read_from_file = 1, 0, 0
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
        import sys

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
        from bisect import bisect_left, bisect_right
        from math import sqrt, gcd

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


# ---常量定义 start---   #
mod1 = int(1e9 + 7)
mod2 = 998244353
inf = float("inf")


# ---常量定义 end---   #

# ------------------------------UserCodeStart-------------------------------#


# ---额外的函数 start--- #
def yes():
    print("YES")


def no():
    print("NO")


# ---额外的函数 end---   #

"""
#         #         #         #           #          #
 #       #           #       #            # #        #
  #     #             #     #             #  #       #
   #   #               #   #              #   #      #
    # #                 # #               #    #     #
     #                   #                #     #    #
     #                   #                #      #   #
     #                   #                #       #  #
     #                   #                #        # #
     #                   #                #          #
"""

dic_1 = [(0, 1), (0, -1), (-1, 0), (1, 0)]
dic_2 = [(0, 1), (0, -1), (-1, 0), (1, 0), (-1, -1), (-1, 1), (1, 1), (1, -1)]

# tt = II()
tt = 1


def yyn():
    def f(score1, score2, set1, set2):
        return (((score1 * 201) + score2) * 4 + set1) * 4 + set2

    dp = [-2] * (201 * 201 * 4 * 4)
    dp[f(0, 0, 0, 0)] = -1

    que = [f(0, 0, 0, 0)]

    for u in que:
        cur = u
        u, set2 = divmod(u, 4)
        u, set1 = divmod(u, 4)
        score1, score2 = divmod(u, 201)

        # 如果这局赢了
        if set1 + 1 <= 3 and set2 < 3:

            set_score = 25 if set1 + set2 < 4 else 15

            if score1 + set_score <= 200:
                for i in range(set_score - 1):
                    if score2 + i <= 200:
                        ncur = f(score1 + set_score, score2 + i, set1 + 1, set2)
                        if dp[ncur] == -2:
                            dp[ncur] = cur
                            que.append(ncur)

            for i in range(set_score + 1, 201):
                if score1 + i > 200 or score2 + i - 2 > 200:
                    break
                ncur = f(score1 + i, score2 + i - 2, set1 + 1, set2)
                if dp[ncur] == -2:
                    dp[ncur] = cur
                    que.append(ncur)

        # 如果这局输了
        if set1 < 3 and set2 + 1 <= 3:

            set_score = 25 if set1 + set2 < 4 else 15

            if score2 + set_score <= 200:
                for i in range(set_score - 1):
                    if score1 + i <= 200:
                        ncur = f(score1 + i, score2 + set_score, set1, set2 + 1)
                        if dp[ncur] == -2:
                            dp[ncur] = cur
                            que.append(ncur)

            for i in range(set_score + 1, 201):
                if score1 + i - 2 > 200 or score2 + i > 200:
                    break
                ncur = f(score1 + i - 2, score2 + i, set1, set2 + 1)
                if dp[ncur] == -2:
                    dp[ncur] = cur
                    que.append(ncur)

    t = II()
    outs = []

    for _ in range(t):
        x, y = MII()

        cx, cy = -1, -1
        for i in range(3):
            if dp[f(x, y, 3, i)] != -2:
                cx, cy = 3, i
                break

        if cx == -1:
            for i in range(2, -1, -1):
                if dp[f(x, y, i, 3)] != -2:
                    cx, cy = i, 3
                    break

        if cx != -1:
            outs.append(f"{cx}:{cy}")

            cur = f(x, y, cx, cy)
            sets = []

            for _ in range(cx + cy):
                prev = dp[cur]
                scores = (cur - prev) // 16
                sets.append(divmod(scores, 201))
                cur = prev

            sets.reverse()
            outs.append(" ".join(f"{a}:{b}" for a, b in sets))
        else:
            outs.append("Impossible")

    print("\n".join(outs))


if __name__ == "__main__":
    for ii in range(tt):
        yyn()
