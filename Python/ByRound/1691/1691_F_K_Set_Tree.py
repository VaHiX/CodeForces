# Problem: CF 1691 F - K-Set Tree
# https://codeforces.com/contest/1691/problem/F

"""
Algorithm: K-Set Tree
Purpose: Calculate the sum of f(r, S) over all possible combinations of vertex r and subset S of size k,
         where f(r, S) is the size of the smallest rooted subtree containing all vertices in S when the tree is rooted at r.

Techniques:
- Tree DFS traversal (post-order)
- Combinatorial mathematics for calculating combinations
- Dynamic programming on trees

Time Complexity: O(n)
Space Complexity: O(n)

The solution uses a post-order DFS traversal to compute for each node the number of nodes in its subtree.
For each node, it calculates how many k-sized subsets are covered by the subtree rooted at that node,
and accumulates the contribution to the final answer.

We calculate combinations using precomputed factorials and modular inverse for efficient computation.
"""

import os
import sys
from io import BytesIO, IOBase

BUFSIZE = 8192


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


sys.stdin, sys.stdout = IOWrapper(sys.stdin), IOWrapper(sys.stdout)
input = lambda: sys.stdin.readline().rstrip("\r\n")

mod = 10**9 + 7
N = 8 * 10**5 + 5
fact = [1] * (N + 1)
factinv = [1] * (N + 1)

# Precompute factorials and their modular inverses
for i in range(2, N + 1):
    fact[i] = fact[i - 1] * i % mod

factinv[-1] = pow(fact[-1], mod - 2, mod)
for i in range(N - 1, 1, -1):
    factinv[i] = factinv[i + 1] * (i + 1) % mod


# Combination function using precomputed factorials
def cmb(a, b):
    if (a < b) or (b < 0):
        return 0
    return fact[a] * factinv[b] % mod * factinv[a - b] % mod


n, k = map(int, input().split())
ikeru = [[] for i in range(n)]
for i in range(n - 1):
    x, y = map(int, input().split())
    x -= 1
    y -= 1
    ikeru[x].append(y)
    ikeru[y].append(x)

ans = 0
tansaku = [0] * n  # Tracking visit status of nodes
tansaku[0] = 1  # Start DFS from node 0
mada = [~0, 0]  # Stack for DFS traversal
des = [0] * n  # des[i] = size of subtree rooted at i
while mada:
    i = mada.pop()
    if i >= 0:
        # First time visiting node i
        for j in ikeru[i]:
            if tansaku[j] == 0:
                mada.append(~j)
                mada.append(j)
                tansaku[j] = 1
    else:
        # Second time visiting node i (post-order DFS)
        i = ~i
        s1 = 1  # Subtree size rooted at i (including itself)
        s2 = 0  # Count of k-sized subsets in this subtree (total)
        a = []  # List of sizes of children subtrees
        for j in ikeru[i]:
            if tansaku[j] == 2:
                s1 += des[j]
                a.append(des[j])
                s2 += cmb(des[j], k)
                s2 %= mod
        des[i] = s1
        a.append(n - s1)
        s2 += cmb(n - s1, k)
        s2 %= mod
        tansaku[i] = 2  # Mark as processed

        # Calculate contribution of node i to the answer
        for j in range(len(a)):
            # For each child with subtree size a[j], calculate contribution
            # (total combinations - combinations within child) * (child size)
            ans += (cmb(n - a[j], k) - (s2 - cmb(a[j], k))) * a[j] * (n - a[j])
            ans %= mod
        # Add contribution of the whole tree (node i is root)
        ans += (cmb(n, k) - s2) * n
        ans %= mod

print(ans)


# https://github.com/VaHiX/CodeForces/