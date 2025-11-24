# Problem: CF 2131 D - Arboris Contractio
# https://codeforces.com/contest/2131/problem/D

"""
D. Arboris Contractio

Purpose:
This code solves the problem of finding the minimum number of operations to reduce the diameter of a tree to its minimum possible value. 
Each operation allows choosing two vertices s and t, removing the path between them, and connecting all vertices on that path directly to s.

Algorithms/Techniques:
- Tree diameter computation using BFS/DFS
- Degree-based analysis to determine optimal contraction points
- Greedy approach based on leaf nodes and their connections

Time Complexity:
O(N) per test case where N is the number of vertices in the tree. 
The algorithm processes each edge once and performs constant time operations for each node.

Space Complexity:
O(N) for storing adjacency list and auxiliary arrays.
"""

import sys

input = sys.stdin.readline
for _ in range(int(input())):
    N = int(input())
    Dic = [[] for _ in range(1 + N)]  # Adjacency list representation of the tree
    for _ in range(N - 1):
        a, b = map(int, input().split())
        Dic[a].append(b)   # Add edge from a to b
        Dic[b].append(a)   # Add edge from b to a (since it's an undirected graph)
    
    V = [0] * (1 + N)  # Count how many times each node appears in leaf connections
    for i in range(1 + N):
        if len(Dic[i]) == 1:  # If the node is a leaf node
            V[Dic[i][0]] += 1  # Increment count for its parent
    
    # The result is sum of all counts minus the maximum count
    # This gives the minimum number of operations needed
    print(sum(V) - max(V) if N > 2 else 0)


# https://github.com/VaHiX/codeForces/