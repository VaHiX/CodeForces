# Problem: CF 1687 C - Sanae and Giant Robot
# https://codeforces.com/contest/1687/problem/C

"""
Algorithm: Union-Find with Segment Union
Time Complexity: O(n + m * α(n)) where α is the inverse Ackermann function
Space Complexity: O(n + m)

The problem involves determining if we can transform array 'a' into array 'b' using copy-paste operations.
Each operation allows copying a segment from 'b' to 'a', but the sum of 'a' must remain unchanged.
We model this by connecting positions that can be updated together using Union-Find.
The core idea is to:
1. Check if the total sums of a and b are equal (if not, impossible)
2. Use Union-Find to group positions that can be updated in sequence
3. Process segments to build connected components that maintain the prefix sums

We process each position and track which segments can update it, connecting segments with Union-Find.
Finally, we verify if all positions can be covered by valid operations.
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


class UnionFind:
    def __init__(self, n):
        self.n = n
        self.parents = [-1] * n
        self.max_ = [i for i in range(n)]
        self.group = n

    def find(self, x):
        if self.parents[x] < 0:
            return x
        else:
            self.parents[x] = self.find(self.parents[x])
            return self.parents[x]

    def union(self, x, y):
        x = self.find(x)
        y = self.find(y)

        if x == y:
            return
        self.group -= 1
        if self.parents[x] > self.parents[y]:
            x, y = y, x

        self.parents[x] += self.parents[y]
        self.parents[y] = x
        if self.max_[y] > self.max_[x]:
            self.max_[x] = self.max_[y]

    def size(self, x):
        return -self.parents[self.find(x)]

    def same(self, x, y):
        return self.find(x) == self.find(y)

    def members(self, x):
        root = self.find(x)
        return [i for i in range(self.n) if self.find(i) == root]

    def roots(self):
        return [i for i, x in enumerate(self.parents) if x < 0]

    def group_count(self):
        return self.group

    def all_group_members(self):
        dic = {r: [] for r in self.roots()}
        for i in range(self.n):
            dic[self.find(i)].append(i)
        return dic

    def __str__(self):
        return "\n".join("{}: {}".format(r, self.members(r)) for r in self.roots())


def solve():
    n, m = map(int, input().split())
    A = list(map(int, input().split()))
    B = list(map(int, input().split()))
    cuma = [0]
    cumb = [0]
    for a in A:
        cuma.append(cuma[-1] + a)
    for b in B:
        cumb.append(cumb[-1] + b)
    if cuma[-1] != cumb[-1]:
        for _ in range(m):
            input()
        print("NO")
        return

    lst = [[] for _ in range(n + 1)]
    cnt = [0] * m
    L = []
    R = []
    for i in range(m):
        l, r = map(int, input().split())
        l -= 1
        lst[l].append(i)
        lst[r].append(i)
        L.append(l)
        R.append(r)

    UF = UnionFind(n + 1)
    stack = []
    tf = [False] * (n + 1)
    for i in range(n + 1):
        if cuma[i] == cumb[i]:
            tf[i] = True
            if i != n:
                UF.union(i, i + 1)
            for j in lst[i]:
                cnt[j] += 1
                if cnt[j] == 2:
                    stack.append(j)

    while stack:
        i = stack.pop()
        l, r = L[i], R[i]
        while 1:
            l = UF.max_[UF.find(l)]
            if l >= r or l >= n:
                break
            UF.union(l, l + 1)
            tf[l] = True
            for j in lst[l]:
                cnt[j] += 1
                if cnt[j] == 2:
                    stack.append(j)
    if all(t for t in tf):
        print("YES")
    else:
        print("NO")


for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/CodeForces/