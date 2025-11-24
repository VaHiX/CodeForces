# Problem: CF 802 O - April Fools' Problem (hard)
# https://codeforces.com/contest/802/problem/O

"""
Algorithm: Binary search on answer with heap optimization
Time Complexity: O(n * log(10^10) * log(n)) 
Space Complexity: O(n)

This solution uses binary search to find the optimal value of 'm' (the threshold).
For each candidate value 'm', we simulate the process of selecting elements from 
two arrays to minimize the sum of selected elements, with at most k elements from 
the first array being selected. Heaps are used to efficiently maintain and 
update the minimum elements during the simulation.
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


class MCFGraph:
    class Edge(NamedTuple):
        src: int
        dst: int
        cap: int
        flow: int
        cost: int

    class _Edge:
        def __init__(self, dst: int, cap: int, cost: int) -> None:
            self.dst = dst
            self.cap = cap
            self.cost = cost
            self.rev: Optional[MCFGraph._Edge] = None

    def __init__(self, n: int) -> None:
        self._n = n
        self._g: List[List[MCFGraph._Edge]] = [[] for _ in range(n)]
        self._edges: List[MCFGraph._Edge] = []

    def add_edge(self, src: int, dst: int, cap: int, cost: int) -> int:
        assert 0 <= src < self._n
        assert 0 <= dst < self._n
        assert 0 <= cap
        m = len(self._edges)
        e = MCFGraph._Edge(dst, cap, cost)
        re = MCFGraph._Edge(src, 0, -cost)
        e.rev = re
        re.rev = e
        self._g[src].append(e)
        self._g[dst].append(re)
        self._edges.append(e)
        return m

    def get_edge(self, i: int) -> Edge:
        assert 0 <= i < len(self._edges)
        e = self._edges[i]
        re = cast(MCFGraph._Edge, e.rev)
        return MCFGraph.Edge(u, v, e.cap, e.flow, e.cost)

    def solve(self, source: int, sink: int) -> int:
        # Not used in this implementation
        pass


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
        ):  # Check if nums2[i] can be beneficial
            heappop(hpq2)
            heappush(hpq2, -nums2[i])
        elif hpq1[0] + nums2[i] < 0:  # This case we need to add nums2[i] to hpq2
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