# Problem: CF 802 L - Send the Fool Further! (hard)
# https://codeforces.com/contest/802/problem/L

"""
Algorithm: Expected Cost on Tree
Approach: Dynamic Programming on Tree with Modular Arithmetic
Time Complexity: O(n)
Space Complexity: O(n)

This solution computes the expected cost of Heidi's random walk on a tree.
The key idea is to use dynamic programming from leaves to root:
- For each node, we compute the expected cost to reach a leaf
- We maintain two values per node:
  - ks[u]: coefficient for the expected value formula
  - bs[u]: constant term for the expected value formula
- For leaf nodes, the expected cost is 0 since Heidi stops there
- For internal nodes, we aggregate results from children and compute
  the expected cost based on probability of choosing each edge

Key Points:
- Each node except root has exactly one parent in the tree
- In the DP, we account for the probability of going through each edge
- Modular inverse is used for division in modular arithmetic
- Special case for leaf nodes with only one edge (they don't send Heidi anywhere)

The expected value at root node (0) gives the final answer.
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


n = II()
mod = 10**9 + 7
path = [[] for _ in range(n)]

us = []
vs = []
cs = []

for i in range(n - 1):
    u, v, c = MII()
    path[u].append(i)
    path[v].append(i)

    us.append(u)
    vs.append(v)
    cs.append(c)

parent = [-1] * n

que = [0]
for u in que:
    for eid in path[u]:
        if parent[u] != eid:
            v = us[eid] + vs[eid] - u
            parent[v] = eid
            que.append(v)

ks = [0] * n
bs = [0] * n

for u in reversed(que):
    if len(path[u]) == 1 and u > 0:
        continue

    # Compute sum of weights and coefficients from children
    sumk = 0
    sumb = 0
    sumc = 0

    for eid in path[u]:
        v = us[eid] + vs[eid] - u
        sumc += cs[eid]
        if parent[v] == eid:
            sumk += ks[v]
            sumb += bs[v]

    # Inverse of (number of children - sumk) to compute coefficient
    rev = pow(len(path[u]) - sumk, -1, mod)
    ks[u] = rev
    bs[u] = (sumb + sumc) * rev % mod

print(bs[0])


# https://github.com/VaHiX/CodeForces/