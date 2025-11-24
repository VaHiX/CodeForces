# Problem: CF 1844 E - Great Grids
# https://codeforces.com/contest/1844/problem/E

"""
Algorithm: Graph Coloring with BFS
Purpose: Determine if a great grid can be constructed given constraints on cells that must have the same letter.
Technique: 
- Model the problem as a graph coloring problem where each cell is a node and constraints create edges.
- Use BFS to traverse the graph and assign colors (0 or 1) to nodes, ensuring no two connected nodes have the same color.
- Check for contradictions during traversal.

Time Complexity: O(n * m + k) where n and m are grid dimensions, and k is number of constraints.
Space Complexity: O(n * m + k) for the graph representation and coloring array.

The problem is modeled as follows:
Each cell in a great grid satisfies: 
- 2x2 subgrid has all 3 letters
- Adjacent cells (sharing an edge) have different letters
- Constraints impose that certain diagonally adjacent cells must have same letter.

We build a graph where constraints define relationships between cells.
Each constraint connects two nodes (representing cells) in the graph with a color difference of 1, 
meaning they are assigned different colors (0 or 1). 
Then we check for consistency using BFS.
"""

import sys
from collections import deque


def input():
    return sys.stdin.readline().rstrip("\n")


show = sys.stdout.write


def print(s):
    return show(str(s) + "\n")


def work():
    n, m, k = map(int, input().split())
    # Create a graph with nodes representing the constraints
    tree = [list() for i in range(n + m - 2)]
    for i in range(k):
        x1, y1, x2, y2 = map(int, input().split())
        # Normalize the constraints to make sure x1 <= x2
        tree[x1 - 1].append((min(y1, y2) + n - 2, int(y2 > y1)))
        tree[min(y1, y2) + n - 2].append((x1 - 1, int(y2 > y1)))

    # Initialize colors array, -1 means unvisited
    ans = [-1] * len(tree)

    # BFS traversal
    for i in range(len(tree)):
        if ans[i] == -1:
            q = deque([i])
            ans[i] = 0
            while q:
                cur = q.popleft()
                for j, k in tree[cur]:
                    if ans[j] == -1:
                        # Set color of neighbor to be opposite of current node's color
                        ans[j] = k ^ ans[cur]
                        q.append(j)
                    elif ans[j] != k ^ ans[cur]:
                        # If neighbor already colored and color is inconsistent, return "NO"
                        return "NO"
    return "YES"


for _ in range(int(input())):
    print(work())


# https://github.com/VaHiX/CodeForces/