# Problem: CF 2063 C - Remove Exactly Two
# https://codeforces.com/contest/2063/problem/C

"""
C. Remove Exactly Two
Problem Description:
Given a tree with n vertices, we must remove exactly two vertices (and all edges incident to them) 
to maximize the number of connected components in the resulting graph.

Algorithms/Techniques:
- Tree traversal and degree analysis to determine optimal vertex removals
- Greedy approach based on vertex degrees

Time Complexity: O(n) per test case, where n is the number of vertices.
Space Complexity: O(n) for storing the adjacency list and indegree array.

Approach:
1. Build the tree from input edges.
2. Find the vertex with maximum degree (this is a key node to consider).
3. Calculate how many components can be formed by removing two such nodes strategically.
4. Special handling for cases where multiple high-degree nodes exist.
"""

import sys

input = sys.stdin.readline
for _ in range(int(input())):
    n = int(input())
    indegree = [0] * (n + 1)
    graph = [[] for _ in range(n + 1)]
    for _ in range(n - 1):
        u, v = map(int, input().split())
        indegree[u] += 1
        indegree[v] += 1
        graph[u].append(v)
        graph[v].append(u)
    x = indegree.index(max(indegree))  # Find the vertex with maximum degree
    result = indegree[x]
    c = 0
    for nx in graph[x]:
        if indegree[nx] == indegree[x]:  # Count neighbors with same max degree
            c += 1
        indegree[nx] -= 1  # Simulate removal of x from neighbor indegrees
    if c >= 2:
        result = indegree[x] * 2 - 1  # Handle case where two high-degree vertices are removed
    else:
        indegree[x] = 0
        x = indegree.index(max(indegree))  # Find new max degree vertex after x removal
        result += indegree[x] - 1  # Add remaining components count
    print(result)


# https://github.com/VaHiX/codeForces/