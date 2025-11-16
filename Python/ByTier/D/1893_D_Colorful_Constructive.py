# Problem: CF 1893 D - Colorful Constructive
# https://codeforces.com/contest/1893/problem/D

"""
Algorithm: Greedy with Priority Queue
Time Complexity: O(n * log n) - where n is the number of cubes, due to heap operations
Space Complexity: O(n) - for storing counts and result arrays

This solution uses a greedy approach to distribute cubes on shelves while satisfying
the minimum colorfulness requirements. We use a max heap (priority queue) to always
place the most frequent color first, ensuring minimal conflicts and optimal distribution.

The algorithm works as follows:
1. Count frequency of each color
2. Create a max heap of colors by frequency
3. For each shelf, distribute colors greedily:
   - Place colors in chunks of size 'd' (minimum required colorfulness)
   - After placing, update the heap with remaining frequencies
4. If heap runs out before filling a shelf, it's impossible

Key insights:
- Greedy placement is optimal for minimizing conflicts
- Using heap enables efficient retrieval of most frequent colors
- The chunk-based approach ensures colorfulness constraint is met
"""

import io
import os
import sys
from collections import defaultdict
from heapq import heappop, heappush

MOD = 998244353
inf = 1 << 60


def solve():
    N, M = read_int_tuple()
    A = read_int_list()
    cnt = defaultdict(int)
    for x in A:
        cnt[x] += 1
    S, D = read_int_list(), read_int_list()
    hp = []
    for x, c in cnt.items():
        heappush(hp, (-c, x))  # Negative for max heap simulation
    res = [[-1] * s for s in S]
    for cur, s, d in zip(res, S, D):  # Process each shelf
        for i in range(0, s, d):  # Distribute in chunks of size 'd'
            cc = min(d, s - i)
            for j in range(cc):
                if not hp:  # If no more colors available
                    print(-1)
                    return
                cur[i + j] = heappop(hp)[1]  # Place most frequent color
            for j in range(cc):
                x = cur[i + j]
                cnt[x] -= 1
                if cnt[x]:
                    heappush(hp, (-cnt[x], x))  # Reinsert updated frequency
    for row in res:
        print(*row)


def main():
    if "AW" in os.environ.get("COMPUTERNAME", ""):
        test_no = 1
        f = open(os.path.dirname(__file__) + f"\\in{test_no}.txt", "r")
        global input
        input = lambda: f.readline().rstrip("\r\n")
    T = read_int()
    for t in range(T):
        solve()


BUFSIZE = 8192


class FastIO(io.IOBase):
    newlines = 0

    def __init__(self, file):
        self._file = file
        self._fd = file.fileno()
        self.buffer = io.BytesIO()
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


class IOWrapper(io.IOBase):
    def __init__(self, file):
        self.buffer = FastIO(file)
        self.flush = self.buffer.flush
        self.writable = self.buffer.writable
        self.write = lambda s: self.buffer.write(s.encode("ascii"))
        self.read = lambda: self.buffer.read().decode("ascii")
        self.readline = lambda: self.buffer.readline().decode("ascii")


def print(*args, **kwargs):
    """Prints the values to a stream, or to sys.stdout by default."""
    sep, file = kwargs.pop("sep", " "), kwargs.pop("file", sys.stdout)
    at_start = True
    for x in args:
        if not at_start:
            file.write(sep)
        file.write(str(x))
        at_start = False
    file.write(kwargs.pop("end", "\n"))
    if kwargs.pop("flush", False):
        file.flush()


sys.stdin, sys.stdout = IOWrapper(sys.stdin), IOWrapper(sys.stdout)
input = lambda: sys.stdin.readline().rstrip("\r\n")


def read_int_list():
    return list(map(int, input().split()))


def read_ints_minus_one():
    return [int(x) - 1 for x in input().split()]


def read_int_tuple():
    return map(int, input().split())


def read_encode_str(d=97):
    return [ord(x) - d for x in input()]


def read_graph(n: int, m: int, d=1):
    g = [[] for _ in range(n)]
    for _ in range(m):
        u, v = map(int, input().split())
        g[u - d].append(v - d)
        g[v - d].append(u - d)
    return g


def read_grid(m: int):
    return [input() for _ in range(m)]


def read_int():
    return int(input())


read_str = input
if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/