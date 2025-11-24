# Problem: CF 1830 A - Copil Copac Draws Trees
# https://codeforces.com/contest/1830/problem/A

"""
A. Copil Copac Draws Trees

Algorithm/Technique: BFS-based traversal to simulate the drawing process of a tree.

The problem simulates a drawing algorithm where vertices are added step-by-step based on 
edges in the order they appear in input. The number of "readings" corresponds to how many
times we have to go through all edges to fully draw the tree.

This solution uses BFS traversal starting from node 0 (vertex 1 in 1-indexed terms). For each 
edge, we determine which direction it goes and compute a depth-like value (dp[u]) indicating
the number of steps needed to reach vertex u, considering edge ordering.

Time Complexity: O(n) per test case
Space Complexity: O(n) for storing adjacency list and auxiliary arrays

"""

from sys import stdin

input = lambda: stdin.readline()[:-1]


def solve():
    n = int(input())
    edge = [[] for i in range(n)]
    for i in range(n - 1):
        a, b = map(lambda x: int(x) - 1, input().split())  # Convert to 0-indexed
        edge[a].append((b, i))  # Add neighbor and edge index
        edge[b].append((a, i))
    dp = [0] * n          # dp[v]: number of readings to reach vertex v
    ord = [-1] * n        # ord[v]: order in which edge connecting to parent was processed
    ord[0] = n            # Root has a large order index (to distinguish from others)
    todo = [0]            # BFS queue starting from root
    while todo:
        v = todo.pop()
        for u, i in edge[v]:
            if ord[u] == -1:  # If not yet visited
                ord[u] = i    # Record the order of edge used to visit u
                if ord[v] > ord[u]:  # If current path is deeper (i.e., we're going "down")
                    dp[u] = dp[v] + 1   # Increment reading count
                else:
                    dp[u] = dp[v]       # Same or shallower - no increment
                todo.append(u)          # Add to BFS queue
    print(max(dp))  # The maximum value of dp gives the total number of readings


for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/codeForces/