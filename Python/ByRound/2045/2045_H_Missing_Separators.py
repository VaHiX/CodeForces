# Problem: CF 2045 H - Missing Separators
# https://codeforces.com/contest/2045/problem/H

"""
Algorithm: Dynamic Programming with String Matching
Techniques: 
- Longest Common Prefix (LCP) computation
- Dynamic Programming with backtracking to reconstruct solution
- Greedy approach to maximize number of words (maximize the count of segments)

Time Complexity: O(n^3) where n is the length of input string S
Space Complexity: O(n^2) for LCP table and DP table

This solution uses dynamic programming to find the maximum number of words 
that can be partitioned from the given string, ensuring all words are 
distinct and sorted in alphabetical order.
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


s = [ord(x) - ord("A") for x in I()]
n = len(s)


def f(i, j):
    return i * n + j


# Precompute longest common prefix (LCP) table
lcp = [0] * (n * n)
for i in range(n - 1, -1, -1):
    for j in range(i, n):
        if s[i] == s[j]:
            msk = f(i, j)
            lcp[msk] = 1
            if j + 1 < n:
                lcp[msk] += lcp[msk + n + 1]

# Dynamic programming setup
dp = [-1] * (n * n)
dp[f(0, 0)] = 1
pre = [-1] * (n * n)

# Fill DP table to maximize number of words
for i in range(n):
    for j in range(i, n - 1):
        msk = f(i, j)
        if dp[msk] != -1:
            # Update with case where we don't extend current segment
            if dp[msk] > dp[msk + 1]:
                dp[msk + 1] = dp[msk]
                pre[msk + 1] = msk
            
            # Calculate next segment based on LCP
            l = lcp[msk + 1]
            if l >= j - i + 1:
                nj = j + 1 + j - i + 1
                if nj >= n:
                    continue
            else:
                nj = j + 1 + l
                if nj >= n or s[nj] < s[i + l]:
                    continue
            
            # Update DP with new segment
            nmsk = f(j + 1, nj)
            if dp[msk] + 1 > dp[nmsk]:
                dp[nmsk] = dp[msk] + 1
                pre[nmsk] = msk

# Find maximum number of words and backtrack to find solution
ans = -1
idx = -1
for i in range(n):
    if dp[f(i, n - 1)] > ans:
        ans = dp[f(i, n - 1)]
        idx = f(i, n - 1)

print(ans)
r = n
outs = []
while idx >= 0:
    # Collect segments from backtracking path
    if pre[idx] // n != idx // n:
        outs.append("".join(chr(ord("A") + s[x]) for x in range(idx // n, r)))
        r = idx // n
    idx = pre[idx]
outs.reverse()

print("\n".join(outs))


# https://github.com/VaHiX/CodeForces/