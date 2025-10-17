# Problem: CF 2022 E1 - Billetes MX (Easy Version)
# https://codeforces.com/contest/2022/problem/E1

"""
E1. Billetes MX (Easy Version)

Purpose:
This code solves a problem where we are given a grid with some cells pre-filled with values,
and we must determine how many ways we can fill the remaining unfilled cells such that
the grid is "beautiful". A beautiful grid satisfies the constraint that for any 2x2 subgrid,
the XOR of its four corners equals zero.

The approach uses graph components to model dependencies between cells due to the XOR constraints.
Each cell in the grid is represented as a node in a bipartite graph where edges indicate XOR constraints.
BFS is used to check if the assignment is consistent and to determine connected components.
For each component, we calculate how many free assignments are possible using powers of 2.

Time Complexity: O(n * m + k + q)
Space Complexity: O(n * m + k)

Algorithms/Techniques:
- BFS on bipartite graph
- XOR constraint propagation
- Union-Find / Component counting with BFS
"""

import io
import os
from collections import deque

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def main():
    m, n, k, q = map(int, input().split())  # Read grid dimensions, number of fixed cells and updates
    neigh = [[] for _ in range(m + n)]  # Build adjacency list for bipartite graph (rows and columns)
    for _ in range(k):
        i, j, num = map(int, input().split())  # Read fixed cell value and position
        i -= 1  # Convert to 0-indexed row
        j = j - 1 + m  # Convert to 0-indexed column (shifted to avoid overlap with rows)
        neigh[i].append((j, num))  # Add edge from row node to col node
        neigh[j].append((i, num))  # Add reverse edge
    visited = [-1] * (m + n)  # Track visited nodes in BFS; -1 means unvisited
    g = 0  # Count of connected components
    queue = deque()  # BFS queue for traversing graph

    # Initialize BFS over all nodes
    for i in range(m + n):
        if visited[i] >= 0:  # Skip already visited node
            continue
        visited[i] = 0  # Start BFS with color 0
        g += 1  # Increment component count
        queue.append(i)  # Add starting node
        while queue:
            index = queue.popleft()  # Get next node to process
            for nextindex, num in neigh[index]:  # Iterate neighbors
                if visited[nextindex] >= 0:  # Already visited?
                    if visited[nextindex] != visited[index] ^ num:  # Inconsistent assignment?
                        print(0)  # Invalid solution
                        return
                    continue
                visited[nextindex] = visited[index] ^ num  # Set consistent color
                queue.append(nextindex)  # Add to BFS queue

    M = 10**9 + 7  # Modulo value for computations
    ans = pow(2, 30 * (g - 1), M)  # Calculate result using modular exponentiation
    print(ans)  # Output final answer


T = int(input())  # Number of test cases
t = 1
while t <= T:
    main()
    t += 1


# https://github.com/VaHiX/codeForces/