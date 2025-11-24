# Problem: CF 1528 A - Parsa's Humongous Tree
# https://codeforces.com/contest/1528/problem/A

"""
Problem: A. Parsa's Humongous Tree

Purpose:
This solution computes the maximum possible "beauty" of a tree where each node has a range [l_i, r_i] 
and we must assign values within these ranges such that the sum of absolute differences over all edges is maximized.

Algorithm:
- This problem uses dynamic programming on trees with a technique called "tree DP".
- For each node, we maintain two values in our DP state:
    - dp0[v]: maximum beauty when assigning value to node v such that it's closer to l[v]
    - dp1[v]: maximum beauty when assigning value to node v such that it's closer to r[v]
- At each node, the DP transition considers:
    - What values to assign to neighbors (either left or right bounds)
    - Which assignments yield the most contribution to total beauty
- The final answer is max(dp0[root], dp1[root])

Time Complexity: O(n) per test case, since we visit each node once in a DFS traversal.
Space Complexity: O(n) for storing tree structure and DP arrays.

"""

from sys import stdin

input = stdin.readline


def Aniket_travel(u, p, d, dp0, dp1, l, r):
    # Recursive DFS to compute DP values bottom-up
    for neighbor in d[u]:
        if neighbor != p:
            Aniket_travel(neighbor, u, d, dp0, dp1, l, r)
    # Compute the DP transitions for current node u based on its children
    dp0[p] += max(dp0[u] + abs(l[p] - l[u]), dp1[u] + abs(l[p] - r[u]))
    dp1[p] += max(dp0[u] + abs(r[p] - l[u]), dp1[u] + abs(r[p] - r[u]))


for _ in range(int(input())):
    n = int(input())
    # Initialize arrays for left and right bounds, and DP values
    l = [0] * (n + 1)
    r = l.copy()
    dp0 = l.copy()
    dp1 = l.copy()
    
    # Read the intervals [l_i, r_i] for each vertex
    for i in range(n):
        x, y = map(int, input().split())
        l[i + 1] = x
        r[i + 1] = y
    
    # Build adjacency list representation of the tree
    d = [[] for i in range(n + 1)]
    for i in range(n - 1):
        u, v = map(int, input().split())
        d[u].append(v)
        d[v].append(u)
    
    # Start DFS from root (vertex 1)
    Aniket_travel(1, 0, d, dp0, dp1, l, r)
    
    # Print the maximum possible beauty
    print(max(dp0[1], dp1[1]))


# https://github.com/VaHiX/codeForces/