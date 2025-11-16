# Problem: CF 1811 G2 - Vlad and the Nice Paths (hard version)
# https://codeforces.com/contest/1811/problem/G2

"""
Algorithm: Dynamic Programming with Sliding Window and Combinatorics
Time Complexity: O(n * k) 
Space Complexity: O(n * k)

This solution uses dynamic programming to count the number of "nice paths" of maximum length.
A nice path is defined as a sequence of tiles where:
1. The length is divisible by k
2. Each block of k consecutive tiles has the same color
3. Blocks are consecutive in the path

The approach:
- Uses a sliding window technique to track valid starting positions based on color constraints
- Maintains dynamic programming states for counting paths ending at each position
- Uses combinatorial mathematics to compute combinations for path extensions
- Tracks maximum length paths and counts how many such paths exist
"""

import io
import os
import sys


class Combi:
    __slots__ = ("fac", "ifac")

    def __init__(self, n: int) -> None:
        assert n < MOD
        self.fac = [1] * (n + 1)
        self.ifac = [1] * (n + 1)
        for i in range(2, n + 1):
            self.fac[i] = self.fac[i - 1] * i % MOD
        self.ifac[n] = pow(self.fac[n], MOD - 2, MOD)
        for i in range(n, 1, -1):
            self.ifac[i - 1] = self.ifac[i] * i % MOD

    def choose(self, n: int, r: int) -> int:
        if r < 0 or r > n:
            return 0
        return (self.fac[n] * self.ifac[n - r] % MOD) * self.ifac[r] % MOD

    def multichoose(self, u: int, k: int) -> int:
        if k < 0 or k > (u + k - 1):
            return 0
        return (self.fac[u + k - 1] * self.ifac[u - 1] % MOD) * self.ifac[k] % MOD

    def permutation(self, n: int, r: int) -> int:
        if r < 0 or r > n:
            return 0
        return self.fac[n] * self.ifac[n - r] % MOD


MOD = 1000000007

cnk = Combi(5000).choose


def solve():
    n, k = read_int_tuple()
    A = read_int_list()
    if k == 1:
        print(1)
        return

    gn = [0] * (n + 1)  # gn[i] is the maximum length of path ending at position i
    cn = [1] + [0] * n  # cn[i] is the count of paths ending at position i with maximum length
    book = [[0] for _ in range(n + 1)]  # book[x] stores positions with color x
    ss = [dict() for _ in range(n + 1)]  # ss[x][pos] = index of position pos in book[x]
    gs = [0] * n  # gs[i] = position where path of length i starts
    for i, x in enumerate(A, 1):
        ss[x][i] = len(book[x])
        book[x].append(i)

        if len(book[x]) > k:
            j = book[x][-k]  # j is the position k steps back in the same color sequence
            gn[i] = max(gn[i - 1], gn[j - 1] + 1)  # update maximum path length at position i
            if gn[i] > gn[i - 1]:
                gs[gn[i]] = i  # update the start position of path of length gn[i]
            tmp = 0
            # For each valid previous position in the same color group
            for j in range(gs[gn[i] - 1], j):
                tmp += cn[j]
                if j + 1 in ss[x]:
                    # Add the number of combinations to extend the path
                    cn[i] = (
                        cn[i] + tmp * cnk(len(book[x]) - ss[x][j + 1] - 2, k - 2)
                    ) % MOD
        else:
            gn[i] = gn[i - 1]  # No new path longer than previous, inherit from left

    # Return the sum of counts for paths of maximum length
    print(sum(b for a, b in zip(gn, cn) if a == gn[-1]) % MOD)


def main():

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


def read_graph(n: int, m: int, d=1):
    g = [[] for _ in range(n)]
    for _ in range(m):
        u, v = map(int, input().split())
        g[u - d].append(v - d)
        g[v - d].append(u - d)
    return g


def read_int():
    return int(input())


read_str = input


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/