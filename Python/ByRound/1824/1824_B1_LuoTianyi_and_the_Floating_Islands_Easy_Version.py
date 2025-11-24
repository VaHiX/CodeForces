# Problem: CF 1824 B1 - LuoTianyi and the Floating Islands (Easy Version)
# https://codeforces.com/contest/1824/problem/B1

"""
Algorithm: Tree Dynamic Programming + Combinatorics
Time Complexity: O(n)
Space Complexity: O(n)

This solution computes the expected number of good islands when k people are randomly placed on k distinct islands in a tree.
The key insight is that for a fixed placement of k people, the good islands are those with minimum total distance to all k people.
We use DFS traversal to calculate for each edge how many ways of placing people result in the edge being crossed (i.e., contributes to the distance sum).

The expected value is calculated using linearity of expectation:
- For each possible placement of k people, we find the number of good islands.
- Since each placement is equally likely, the expectation is the average number of good islands over all placements.
- We compute the contribution of each edge to the number of good islands.
"""

import os
import sys
from io import BytesIO, IOBase


class IOWrapper(IOBase):
    def __init__(self, file):
        self.buffer = FastIO(file)
        self.flush = self.buffer.flush
        self.writable = self.buffer.writable
        self.write = lambda s: self.buffer.write(s.encode("ascii"))
        self.read = lambda: self.buffer.read().decode("ascii")
        self.readline = lambda: self.buffer.readline().decode("ascii")


BUFSIZE = 4096


class FastIO(IOBase):
    newlines = 0

    def __init__(self, file):
        self._fd = file.fileno()
        self.buffer = BytesIO()
        self.writable = "x" in file.mode or "r" not in file.mode
        self.write = self.buffer.write if self.writable else None

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

    def read(self):
        while True:
            b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
            if not b:
                break
            ptr = self.buffer.tell()
            self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
        self.newlines = 0
        return self.buffer.read()


sys.stdin = IOWrapper(sys.stdin)
sys.stdout = IOWrapper(sys.stdout)
input = lambda: sys.stdin.readline().rstrip("\r\n")


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


def GMI():
    return map(lambda x: int(x) - 1, input().split())


def LGMI():
    return list(map(lambda x: int(x) - 1, input().split()))


inf = float("inf")


class Factorial:
    def __init__(self, N, mod) -> None:
        N += 1
        self.mod = mod
        self.f = [1 for _ in range(N)]
        self.g = [1 for _ in range(N)]
        for i in range(1, N):
            self.f[i] = self.f[i - 1] * i % self.mod
        self.g[-1] = pow(self.f[-1], mod - 2, mod)
        for i in range(N - 2, -1, -1):
            self.g[i] = self.g[i + 1] * (i + 1) % self.mod

    def fac(self, n):
        return self.f[n]

    def fac_inv(self, n):
        return self.g[n]

    def comb(self, n, m):
        if n < m or m < 0 or n < 0:
            return 0
        return self.f[n] * self.g[m] % self.mod * self.g[n - m] % self.mod

    def perm(self, n, m):
        if n < m or m < 0 or n < 0:
            return 0
        return self.f[n] * self.g[n - m] % self.mod

    def catalan(self, n):
        return (self.comb(2 * n, n) - self.comb(2 * n, n - 1)) % self.mod

    def inv(self, n):
        return self.f[n - 1] * self.g[n] % self.mod


mod = 10**9 + 7
fact = Factorial(2 * 10**5, mod)

# Read input
n, k = MII()
path = [[] for _ in range(n)]
for _ in range(n - 1):
    u, v = GMI()
    path[u].append(v)
    path[v].append(u)

# Special case where k is odd - each configuration will have exactly one good island
if k % 2:
    print(1)
    exit()

# DFS traversal to compute sizes and contributions
dfs_order = []
parent = [-1] * n

stack = [0]
while stack:
    u = stack.pop()
    for v in path[u]:
        if v != parent[u]:
            dfs_order.append(v)
            parent[v] = u
            stack.append(v)

dfs_order.reverse()

ans = 0
size = [1] * n
for i in dfs_order:
    size[parent[i]] += size[i]
    # For each node, calculate how many ways to choose k/2 people from the subtree (size[i]), and how many from the remaining part (n-size[i])
    ans += fact.comb(size[i], k // 2) * fact.comb(n - size[i], k // 2)
    ans %= mod

# Final result based on combinatorics and expected value calculation
print((ans * fact.fac(k) * fact.fac(n - k) * fact.fac_inv(n) + 1) % mod)


# https://github.com/VaHiX/CodeForces/