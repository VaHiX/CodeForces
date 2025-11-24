# Problem: CF 1800 G - Symmetree
# https://codeforces.com/contest/1800/problem/G

"""
Symmetree Problem Solution

Algorithm:
- This solution uses a tree hashing approach to determine if a tree is symmetric.
- Each subtree is assigned a hash value based on its structure.
- For symmetry, the children of each node must be arranged such that the hash of left subtree 
  matches the hash of right subtree when mirrored.

Time Complexity: O(n) where n is the number of nodes, as each node is visited a constant number of times.
Space Complexity: O(n) for storing the tree structure and auxiliary arrays.

Techniques:
- Tree traversal using stack (iterative)
- Hash-based subtree comparison
- Mirror symmetry checking using hash values
"""

import os
import random
import sys
from collections import Counter
from io import BytesIO, IOBase

BUFSIZE = 4096


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


mod = 998244353
inf = 10**15


def solve():
    n = II()
    # Generate a random seed for hashing to ensure unique values
    a = random.getrandbits(30) + 96267167
    # Initialize adjacency list for the tree
    dct = [[] for i in range(n)]
    # Arrays for hashing values
    A = [a] * n
    B = [0] * n
    C = [1] * n
    # Build adjacency list
    for i in range(n - 1):
        u, v = GMI()
        dct[u].append(v)
        dct[v].append(u)

    # Initialize depth and parent arrays
    d = [0] + [-1] * (n - 1)
    fa = [-1] * n
    # Stack for iterative DFS traversal
    stack = [0]

    while stack:
        x = stack.pop()
        if x >= 0:
            # Mark node as visited and push its children
            stack.append(~x)
            for y in dct[x]:
                if y == fa[x]:
                    continue
                stack.append(y)
                d[y] = d[x] + 1
                fa[y] = x
        else:
            # Process the node after all children are handled
            x = ~x
            # Update hash values for current node
            A[x] = (A[x] + B[x] + C[x]) % mod
            if fa[x] >= 0:
                # Update parent's hash values
                B[fa[x]] = (B[fa[x]] + A[x]) % mod
                C[fa[x]] = (C[fa[x]] * A[x]) % mod
    # Start from root node (node 0) 
    pos = 0

    while True:
        # Count hash values of children
        cnt = Counter()
        for x in dct[pos]:
            if x == fa[pos]:
                continue
            cnt[A[x]] += 1
        cc = 0
        y = 0
        for x, c in cnt.items():
            if c & 1:
                cc += 1
                y = x
                if cc == 2:
                    print("NO")
                    return
        # If all children have even count, tree is symmetric so far
        if cc == 0:
            print("YES")
            return
        # Find child that has the odd count hash value to continue traversal
        for x in dct[pos]:
            if x == fa[pos]:
                continue
            if A[x] == y:
                pos = x
                break


for _ in range(II()):
    solve()


# https://github.com/VaHiX/CodeForces/