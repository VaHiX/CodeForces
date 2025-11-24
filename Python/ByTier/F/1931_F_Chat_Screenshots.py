# Problem: CF 1931 F - Chat Screenshots
# https://codeforces.com/contest/1931/problem/F

"""
Algorithm: Topological Sort
Purpose: Determine if there exists a valid ordering of participants such that all k screenshots are consistent.
Approach:
    - For each screenshot, we extract relative orderings between adjacent elements.
    - Build a directed graph where an edge from a to b means "a must come before b".
    - Perform topological sort to check if a valid ordering exists.
Time Complexity: O(n * k) - Each element is visited at most once in the graph traversal.
Space Complexity: O(n) - For storing graph and degrees.
"""

import sys

input = sys.stdin.readline


def solve():
    ans = ["NO", "YES"]
    n, k = map(int, input().split())
    g = [[] for i in range(n + 1)]  # Adjacency list for the graph
    deg = [0 for i in range(n + 1)]  # In-degree of each node
    
    for i in range(k):
        ls = list(map(int, input().split()))
        # Process each adjacent pair in the screenshot
        for i in range(2, n):  # start from index 2 to n-1
            g[ls[i - 1]].append(ls[i])  # Add edge: ls[i-1] -> ls[i]
            deg[ls[i]] += 1  # Increment in-degree of ls[i]
    
    # Find all nodes with in-degree 0 (starting points)
    fuck = [i for i in range(1, n + 1) if deg[i] == 0]
    
    # Process nodes in topological order
    for i in fuck:
        for j in g[i]:  # For each neighbor
            deg[j] -= 1  # Reduce in-degree
            if deg[j] == 0:  # If in-degree becomes 0, add to queue
                fuck.append(j)
    
    # If we processed all nodes, then a valid ordering exists
    print(ans[len(fuck) == n])


for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/CodeForces/