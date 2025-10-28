# Problem: CF 2126 F - 1-1-1, Free Tree!
# https://codeforces.com/contest/2126/problem/F

"""
F. 1-1-1, Free Tree!
Algorithms/Techniques: DFS traversal, tree manipulation with bit operations, query updates with cost tracking.

Time Complexity:
- Preprocessing (DFS): O(n)
- Each query: O(1)
- Overall: O(n + q) per test case

Space Complexity:
- O(n) for storing tree, parent array, rank, cost counters and auxiliary arrays.

This solution uses a DFS traversal to initialize the structure of the tree. For each node,
it tracks the cost contribution from edges incident on it based on color differences.
When repainting a vertex, we efficiently update the global cost by modifying the 
cost counter in the parent node and adjusting the answer accordingly.
"""

import os
import random
import sys
from collections import Counter
from io import BytesIO, IOBase

r = random.randint(1, 100000000)  # Random number for XOR operation


def main():
    def dfs(root):
        res = 0
        stack = [(root, -1)]
        while stack:
            node, father = stack.pop()
            fa[node] = father
            for child, c in tree[node]:
                if fa[child] == -1 and child:  # If not visited yet and not the root
                    rank[child] = c
                    cost[node][a[child] ^ r] += c  # Accumulate cost by XOR of color and random value
                    if a[child] != a[node]:  # If colors differ, add edge cost
                        res += c
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
            ans += cost[v][a[v] ^ r]  # Adjusting the answer by removing old contribution
            ans -= cost[v][x ^ r]    # Adding new contribution
            if u != -1:
                if a[u] == a[v]:     # If parent and current node had same color before update
                    ans += rank[v]   # Add edge cost since they differ now
                if a[u] == x:        # If parent and new color are same
                    ans -= rank[v]   # Subtract edge cost since they don't differ anymore
                cost[u][a[v] ^ r] -= rank[v]  # Update cost in parent's counter
                cost[u][x ^ r] += rank[v]
            a[v] = x                   # Update color of node
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


# https://github.com/VaHiX/CodeForces/