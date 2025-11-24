# Problem: CF 1776 F - Train Splitting
# https://codeforces.com/contest/1776/problem/F

"""
Code Purpose:
This code solves the problem of splitting train routes among companies such that:
1. Each company operates at least one route.
2. For any single company, there exists a pair of cities that cannot be reached using only that company's routes.
3. For any two companies, all cities can be reached using only routes operated by those two companies.

Algorithm:
- The solution considers two main cases:
  - If there exists a vertex with degree less than n-1, we assign one company to all edges connected to this vertex.
  - Otherwise, we use a 3-company assignment strategy.

Time Complexity:
O(n + m) - For each test case, we perform a single pass over the vertices and edges.

Space Complexity:
O(n + m) - To store the adjacency list representation of the graph.
"""

import sys

input = sys.stdin.buffer.readline

for _ in range(int(input())):
    n, m = map(int, input().split())
    g = [[] for _ in range(n + 1)]  # Adjacency list for graph
    d = [0] * (n + 1)  # Degree of each vertex
    for i in range(m):
        u, v = map(int, input().split())
        g[u].append((v, i))  # Store neighbor and edge index
        g[v].append((u, i))
        d[u] += 1
        d[v] += 1
    
    # Find the vertex with minimum degree
    k = 1
    for i in range(1, n + 1):
        if d[i] < d[k]:
            k = i
    
    # If the minimum degree is less than n - 1, we can split into 2 companies
    if d[k] < n - 1:
        print(2)
        ans = [1] * m  # Initialize all edges to company 1
        # Assign company 2 to all edges connected to the vertex with minimum degree
        for _, i in g[k]:
            ans[i] = 2
        print(*ans)
    else:
        # If all vertices have degree n - 1, use 3 companies
        print(3)
        ans = [1] * m  # Initialize all edges to company 1
        # Assign company 2 to all edges from vertex 1
        for _, i in g[1]:
            ans[i] = 2
        # Assign company 3 to one of the edges from vertex 1
        ans[g[1][0][1]] = 3
        print(*ans)


# https://github.com/VaHiX/CodeForces/