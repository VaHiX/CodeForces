# Problem: CF 1572 A - Book
# https://codeforces.com/contest/1572/problem/A

"""
Book
Algorithm: Topological Sort + Dynamic Programming
Time Complexity: O(V + E) where V is number of chapters and E is total dependencies
Space Complexity: O(V + E) for adjacency list and auxiliary arrays

This problem models a directed graph where each chapter points to its required chapters.
We perform a topological sort using DFS to detect cycles. If a cycle exists, return -1.
Otherwise, we compute the maximum depth (number of reads needed) using dynamic programming on the topologically sorted order.
"""

import sys

input = sys.stdin.readline


class graph(object):
    def __init__(self, n):
        self.arr = [[] for _ in range(n)]  # Adjacency list representation
        self.vertices = n

    def add(self, v, u):
        self.arr[v].append(u)  # Add edge from v to u

    def dfs(self):
        visited = [0] * self.vertices  # 0: unvisited, 1: visiting, 2: visited
        topsort = [0] * self.vertices  # Stores topological order
        stack = []
        k = self.vertices - 1  # Index for topological sort result
        for i in range(self.vertices):
            if not visited[i]:
                stack.append(i)
                while stack:
                    v = stack[-1]
                    if not visited[v]:
                        visited[v] = 1  # Mark as visiting
                        for u in self.arr[v]:
                            if not visited[u]:
                                stack.append(u)
                            elif visited[u] == 1:  # Back edge detected => cycle
                                return -1
                    else:
                        if visited[v] == 1:
                            topsort[k] = v  # Add to topological order
                            k -= 1
                        visited[v] = 2  # Mark as visited
                        stack.pop()
        dp = [0] * self.vertices  # Maximum number of reads needed to reach each chapter
        for v in topsort:
            for u in self.arr[v]:
                dp[u] = max(dp[u], dp[v] + int(u > v))  # Update depending on dependency requirements
        return max(dp) + 1


def solve():
    n = int(input())
    g = graph(n)
    for i in range(n):
        arr = [int(v) for v in input().split()]
        for j in range(1, len(arr)):
            g.add(i, arr[j] - 1)  # Convert to 0-indexed
    print(g.dfs())


if __name__ == "__main__":
    t = 1
    t = int(input())
    while t > 0:
        solve()
        t -= 1


# https://github.com/VaHiX/codeForces/