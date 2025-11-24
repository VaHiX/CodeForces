# Problem: CF 1090 K - Right Expansion Of The Mind
# https://codeforces.com/contest/1090/problem/K

"""
Problem A. Right Expansion Of The Mind

Algorithm:
This problem involves grouping people based on whether their "expanded minds" are mutually subsequences.
The expanded mind is an infinite string defined as s + t + t + t + ... where the first part is s and then infinite t's.

Key insight:
- If the expanded minds of two people a and b are mutually subsequences, then the strings s1 and t1 (for person 1) 
  and s2 and t2 (for person 2) have a relationship based on the structure.
- The approach uses the concept: for strings s1,t1 and s2,t2:
    - If t2 forms a subsequence of t1, then expand s1 to include only characters from t1 that are not in t2.
    - Similarly check for other combinations.

Complexity:
Time complexity: O(n * L) where L is the maximum length of strings (due to processing each person's string).
Space complexity: O(n * L) for storing and processing mappings.
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
        from collections import defaultdict
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

    class notest_notest:
        def __init__(self, n) -> None:
            self.n = n
            self.pre = []
            self.cur = []
            self.notest = [-1] * n

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
vis = defaultdict(list)
for idx in range(1, t + 1):
    s1, s2 = LI()
    l1 = [ord(c) - ord("a") for c in s1] # Convert string to list of indices (0-25)
    l2 = [ord(c) - ord("a") for c in s2] # Same for second string
    msk = 0
    for c in l2:
        msk |= 1 << c # Create bitmask from characters in s2
    i = len(l1) - 1  # Start from end of first string
    while i >= 0 and msk >> l1[i] & 1: # If character at i-th position in l1 is present in l2
        i -= 1 # Skip it to avoid duplication of t part
    s1 = s1[: i + 1] # Truncate s1 by removing repeated characters
    vis[(msk, s1)].append(idx) # Group people with same truncated s1 and mask (t's) in one group
print(len(vis))
outs = []
for x in vis.values():
    outs.append(f'{len(x)} {" ".join(map(str, x))}')
print("\n".join(outs))



# https://github.com/VaHiX/codeForces/