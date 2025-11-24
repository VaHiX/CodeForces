# Problem: CF 1070 L - Odd Federalization
# https://codeforces.com/contest/1070/problem/L

"""
Algorithm: Odd Federalization
Purpose: Split cities into states such that each city has an even number of inner roads.
Approach: 
1. First check if all degrees are even - if so, one state is sufficient.
2. Otherwise, model the problem using XOR basis to find minimum number of states.
3. Use Gaussian elimination over GF(2) to find the minimum number of states required.

Time Complexity: O(n^2 + m) where n is number of cities and m is number of roads.
Space Complexity: O(n^2) for storing adjacency information and basis vectors.

Techniques:
- Gaussian elimination over GF(2) (XOR basis)
- Degree calculation and parity checking
- Graph representation using bitmasks
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


class XorBase:
    n = 30

    def __init__(self):
        self.base = [0] * self.n

    def add(self, num):
        for i in range(num.bit_length() - 1, -1, -1):
            if (num >> i) & 1:
                if self.base[i] == 0:
                    self.base[i] = num
                    return
                else:
                    num ^= self.base[i]

    def realBase(self):
        for i in range(self.n):
            for j in range(i - 1, -1, -1):
                if self.base[i] ^ self.base[j] < self.base[i]:
                    self.base[i] ^= self.base[j]
        return [val for val in self.base if val]


t = II()
outs = []
for _ in range(t):
    I()
    n, m = MII()
    degs = [0] * n
    path = [0] * n
    vpath = [[] for _ in range(n)]
    for _ in range(m):
        u, v = GMI()
        path[u] |= 1 << v + 1
        path[v] |= 1 << u + 1
        degs[u] ^= 1
        degs[v] ^= 1
    if max(degs) == 0:
        outs.append("1")
        outs.append(" ".join("1" for _ in range(n)))
    else:
        XorBase.n = n + 1
        for i in range(n):
            if degs[i]:
                path[i] |= 1
                path[i] |= 1 << i + 1
        base = XorBase()
        for v in path:
            base.add(v)
        tmp = base.realBase()
        k = len(tmp)
        idxs = [x.bit_length() - 2 for x in tmp]
        ans = [0] * n
        for i in range(k):
            ans[idxs[i]] = tmp[i] & 1
            for j in range(idxs[i]):
                if tmp[i] >> (j + 1) & 1:
                    ans[i] ^= ans[j]
        for i in range(n):
            x = 0
            for j in vpath[i]:
                if ans[i] == ans[j]:
                    x ^= 1
            assert x == 0
        outs.append("2")
        outs.append(" ".join(str(x + 1) for x in ans))
print("\n".join(outs))


# https://github.com/VaHiX/CodeForces/