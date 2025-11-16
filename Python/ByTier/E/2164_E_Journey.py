# Problem: CF 2164 E - Journey
# https://codeforces.com/contest/2164/problem/E

"""
Algorithm: Minimum Spanning Tree with modification for odd-degree vertices
Technique: Union-Find (Kruskal's algorithm) + Tree DP

Time Complexity: O(m α(n) + n) where α is the inverse Ackermann function
Space Complexity: O(n)

This solution computes the minimum cost to traverse all edges of a graph 
and return to the starting vertex, considering that transfers between 
vertices cost the maximum edge index on the path used for transfer.

The approach involves:
1. Building a Minimum Spanning Tree (MST) using Union-Find
2. For each component, calculating the contribution of odd-degree vertices 
   to the total cost using tree dynamic programming
3. The final answer is the sum of MST edge weights plus adjustments 
   for odd-degree vertices
"""

import io

input = io.BufferedReader(io.FileIO(0), 1 << 18).readline


class KRT:
    def __init__(self, N):
        self.V = 2 * N - 1  # Virtual nodes for union-find
        self.parent = [-1] * self.V
        self.cur = N  # Next available virtual node index
        self.connect = [[] for _ in range(self.V)]

    def find(self, v):
        stack = []
        while self.parent[v] >= 0:  # While v is not root
            stack.append(v)
            v = self.parent[v]
        while stack:  # Path compression
            self.parent[stack.pop()] = v
        return v

    def union(self, a, b):
        a, b = self.find(a), self.find(b)
        if a == b:  # Already connected
            return False
        if self.parent[a] > self.parent[b]:  # Ensure a has smaller rank
            a, b = b, a
        self.parent[self.cur] = self.parent[a] + self.parent[b]  # Union by rank
        self.parent[a], self.parent[b] = self.cur, self.cur
        self.connect[self.cur].extend([a, b])  # Record connections for tree traversal
        self.cur += 1
        return True


def solve():
    n, m = map(int, input().split())
    uf = KRT(n)
    V = uf.V
    dp = [0] * V
    degree = [0] * n
    ans = 0
    for _ in range(m):
        u, v, w = map(int, input().split())
        u, v = u - 1, v - 1
        degree[u] += 1
        degree[v] += 1
        ans += w
        if uf.union(u, v):  # If union successful, it's part of MST
            u = uf.find(u)
            dp[u] = w
        else:  # If already connected, update edge weight for non-MST edge
            u = uf.find(u)
            dp[u] = min(dp[u], w)
    connect = uf.connect

    i = [*map(iter, connect)]  # Iterator for tree connections
    stack = [(V - 1, None)]  # DFS stack for tree traversal
    odd = [0] * V  # Count of odd-degree vertices in subtree
    while stack:
        u, v = stack.pop()
        if v is None:  # This is a leaf or root in DFS traversal
            if u < n:
                odd[u] = degree[u] & 1  # If degree is odd, mark as 1
        else:  # This is a child processing
            odd[u] += odd[v]  # Accumulate odd count from children
        try:
            while True:
                v = next(i[u])  # Get next connection
                dp[v] = min(dp[u], dp[v])  # Minimum edge weight in subtree
                stack.append((u, v))  # Add pair to processing
                stack.append((v, None))  # Add leaf to processing
                break
        except StopIteration:
            ans += dp[u] * (odd[u] >> 1)  # Add contribution of odd vertices
            odd[u] &= 1  # Keep only 0 or 1 for current node

    print(ans)


for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/CodeForces/