# Problem: CF 1790 F - Timofey and Black-White Tree
# https://codeforces.com/contest/1790/problem/F

"""
Algorithm: 
- Build a tree from input edges
- Perform DFS to find parent relationships and compute distances from initial black node (c0)
- For each operation:
    - Traverse up the tree from newly colored black vertex to root
    - Update minimum distances from current black vertices
    - Track the minimum distance between all pairs of black vertices

Time Complexity: O(n) for each test case, as each node is visited at most once per operation in the worst case.
Space Complexity: O(n) for storing tree structure, parent array, and distance array.

This approach efficiently maintains the minimum distance between all pairs of black vertices by propagating updates from newly colored nodes up to their ancestors.
"""

import os
import sys
from io import BytesIO, IOBase

INF = 10**9


def read_ls(func=int):
    return list(map(func, input().split(" ")))


def solve():
    n, c0 = read_ls()
    c0 -= 1 # Convert to 0-based indexing
    c = read_ls(lambda x: int(x) - 1) # Convert to 0-based indexing
    tree = [[] for _ in range(n)]
    for _ in range(n - 1):
        i, j = read_ls(lambda x: int(x) - 1)
        tree[i].append(j)
        tree[j].append(i)
    res = []
    parent = [-1] * n
    cur = INF
    dis = [INF] * n

    def get_parent(node):
        st = [node]
        while st:
            node = st.pop()
            for nb in tree[node]:
                if nb != parent[node]:
                    parent[nb] = node
                    st.append(nb)

    get_parent(c0)
    dis[c0] = 0
    for ci in c:
        v = ci
        d = 0
        # Traverse from the newly colored node up to the root
        # Update distances and check minimum distance with ancestors
        while v != -1 and d < cur:
            cur = min(cur, d + dis[v]) # Update global minimum distance
            dis[v] = min(dis[v], d)    # Update distance to current node
            v = parent[v]              # Move to parent
            d += 1                     # Increment distance
        res.append(cur)

    print(*res)


def main():
    for _ in range(int(input())):
        solve()


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
if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/