# Problem: CF 2126 F - 1-1-1, Free Tree!
# https://codeforces.com/contest/2126/problem/F

# F. 1-1-1, Free Tree!
# Purpose:
#   Efficiently maintain and update the total cost of a tree where edges cost c if they connect vertices with different colors.
#   Uses DFS to precompute initial state and maintains counters for each node's edge costs to enable fast query updates.
# Algorithms/Techniques:
#   - Tree DFS traversal
#   - Fast IO optimization
#   - Dynamic cost tracking using Counter per node
# Time Complexity:
#   - O(n + q) per test case: preprocessing (DFS) is O(n), and each query is O(1)
# Space Complexity:
#   - O(n) for storing tree structure, colors, parent info, rank, and cost counters

import os
import random
import sys
from collections import Counter
from io import BytesIO, IOBase

r = random.randint(1, 100000000)

def main():
    def dfs(root):
        res = 0
        stack = [(root, -1)]
        while stack:
            node, father = stack.pop()
            fa[node] = father
            for child, c in tree[node]:
                if fa[child] == -1 and child:  # If not visited yet and is not root
                    rank[child] = c  # Store the edge weight to parent
                    cost[node][a[child] ^ r] += c  # Add to cost counter at node for color^r
                    if a[child] != a[node]:
                        res += c  # Increment total cost if colors differ
                    stack.append((child, node))
        return res

    for _ in range(int(input())):
        n, q = map(int, input().split())
        a = list(map(int, input().split()))
        tree = [[] for _ in range(n)]
        for _ in range(n - 1):
            u, v, c = map(int, input().split())
            tree[u - 1].append((v - 1, c))
            tree[v - 1].append((u - 1, c))
        fa = [-1] * n
        rank = [0] * n
        cost = [Counter() for _ in range(n)]
        ans = dfs(0)
        for _ in range(q):
            v, x = map(int, input().split())
            v -= 1
            u = fa[v]
            # Adjust global sum by adding/removing cost from this node's counter
            ans += cost[v][a[v] ^ r]  # Add cost of edges connected to current color at v
            ans -= cost[v][x ^ r]     # Remove cost of edges for new color at v
            if u != -1:
                # Adjust answer if parent's color changed due to node change
                if a[u] == a[v]:
                    ans += rank[v]
                if a[u] == x:
                    ans -= rank[v]
                # Update the counters in the parent for the old and new colors
                cost[u][a[v] ^ r] -= rank[v]
                cost[u][x ^ r] += rank[v]
            a[v] = x
            print(ans)

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
if __name__ == "__main__":
    main()


# https://github.com/VaHiX/codeForces/