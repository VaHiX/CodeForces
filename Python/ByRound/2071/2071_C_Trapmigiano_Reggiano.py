# Problem: CF 2071 C - Trapmigiano Reggiano
# https://codeforces.com/contest/2071/problem/C

"""
C. Trapmigiano Reggiano

Purpose:
This code solves a problem where we are given a tree with n vertices, a starting vertex st,
and a trap vertex en. We must find a permutation of the vertices such that a mouse moving
from st will be forced to reach en after exactly n steps (each step moves the mouse toward
the cheese appearing at the next vertex in the permutation, unless it's already there).
The solution uses BFS from the trap vertex `en` and reverses the order to construct a valid permutation.

Algorithms:
- Breadth-First Search (BFS) to traverse the tree from the trap vertex `en`
- Reverse BFS traversal to generate one valid permutation

Time Complexity: O(n)
Space Complexity: O(n)

Input Format:
- First line contains number of test cases t
- Each test case starts with n, st, en
- Then n-1 edges follow

Output Format:
- A permutation of vertices such that the mouse is forced to end at en
- If impossible, output -1
"""

import sys

input = sys.stdin.readline
for i in range(int(input())):
    n, st, en = map(int, input().split())
    g = [[] for j in range(n)]
    for j in range(n - 1):
        u, v = map(int, input().split())
        g[u - 1].append(v - 1)
        g[v - 1].append(u - 1)
    s = [en - 1]         # Stack for BFS traversal, starting from trap vertex
    t = [en]             # List to store the result permutation in reverse order
    vis = [(0 if j != en - 1 else 1) for j in range(n)]  # Visited array, mark trap as visited
    while s:
        parent = s.pop()     # Pop current node from stack
        for child in g[parent]:   # Iterate through neighbors
            if not (vis[child]):  # If not yet visited
                s.append(child)   # Add to stack for further exploration
                t.append(child + 1)  # Store vertex number (1-indexed)
                vis[child] = 1     # Mark as visited
    print(*t[::-1])         # Output the permutation in reverse order


# https://github.com/VaHiX/codeForces/