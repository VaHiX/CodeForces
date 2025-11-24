# Problem: CF 1823 E - Removing Graph
# https://codeforces.com/contest/1823/problem/E

"""
Algorithm: Game Theory with DSU (Disjoint Set Union)
This problem involves a game on a graph where each vertex has degree 2, meaning the graph consists of cycles and paths.
The key insight is that we can model this using DSU to find connected components, then calculate the nimber (XOR) of each component's size.
For each component of size x, if x < L + R, we compute x // L and XOR it into the final result.
If the final XOR is 0, Bob wins; otherwise, Alice wins.
Time Complexity: O(N * α(N)) where α is the inverse Ackermann function, due to DSU operations
Space Complexity: O(N) for DSU and auxiliary data structures
"""
import os
import sys
from collections import defaultdict as ddic
from io import BytesIO, IOBase


class DSU:
    def __init__(self, N):
        self.par = list(range(N))  # Parent array for DSU
        self.sz = [1] * N          # Size of each component

    def find(self, x):
        # Path compression for efficiency
        if self.par[x] != x:
            self.par[x] = self.find(self.par[x])
        return self.par[x]

    def union(self, x, y):
        # Union by size for efficiency
        xr, yr = self.find(x), self.find(y)
        if xr == yr:
            return False
        if self.sz[xr] < self.sz[yr]:
            xr, yr = yr, xr
        self.par[yr] = xr
        self.sz[xr] += self.sz[yr]
        self.sz[yr] = self.sz[xr]
        return True

    def size(self, x):
        return self.sz[self.find(x)]


def solve():
    N, L, R = readlist()  # Read n, l, r
    dsu = DSU(N)
    # Read all edges and build the DSU structure
    for _ in range(N):
        u, v = readlist()
        u -= 1  # Convert to 0-indexed
        v -= 1
        dsu.union(u, v)
    
    # Group vertices by their component root and count sizes
    sizes = ddic(int)
    for u in range(N):
        sizes[dsu.find(u)] += 1
    
    sizes = list(sizes.values())  # Extract component sizes
    
    ans = 0
    # For each component, calculate contribution to nimber
    for x in sizes:
        if x < L + R:
            ans ^= x // L  # XOR the quotient into final answer
    return ans


def main():
    T = 1

    for tc in range(T):
        ans = solve()

        print("Alice" if ans else "Bob")  # Alice wins if xor is non-zero


BUFSIZE = 8192


class FastIO(IOBase):
    newlines = 0

    def __init__(self, file):
        self._file = file
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


sys.stdin, sys.stdout = IOWrapper(sys.stdin), IOWrapper(sys.stdout)
input = lambda: sys.stdin.readline().rstrip("\r\n")
readint = lambda: int(input())
readlist = lambda: list(map(int, input().split()))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/