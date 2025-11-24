# Problem: CF 1677 C - Tokitsukaze and Two Colorful Tapes
# https://codeforces.com/contest/1677/problem/C

"""
Algorithm: 
This code solves the problem of maximizing the beauty of two colored tapes by assigning values to colors.
The approach uses cycle detection in a permutation graph to determine optimal value assignments.

Key idea:
- Build a mapping from colors in tape b to colors in tape a.
- Find cycles in the permutation graph.
- For odd-length cycles, we must assign opposite values to prevent conflicts.
- Use greedy assignment to maximize abs difference.

Time Complexity: O(n) - Linear traversal for building graph and finding cycles.
Space Complexity: O(n) - For storing node mapping and visited array.
"""

import sys

t = int(sys.stdin.readline().strip())
for _ in range(t):
    n = int(sys.stdin.readline().strip())
    a = [0] + [*map(int, sys.stdin.readline().strip().split())] # 1-indexed tape a
    b = [0] + [*map(int, sys.stdin.readline().strip().split())] # 1-indexed tape b
    node = [0 for i in range(n + 1)] # node[i] represents where color i in tape b maps to in tape a
    
    # Build mapping: node[color_in_b] = color_in_a
    for i in range(1, n + 1):
        node[b[i]] = a[i]
    
    vis = [0 for i in range(n + 1)] # Visited array to track cycle detection
    k = 0 # Count of odd-length cycles
    
    # Traverse each unvisited node to find cycles
    for i in range(1, n + 1):
        if vis[i]:
            continue
        now = i
        c = 0 # Cycle length
        while not vis[now]:
            c += 1
            vis[now] = 1
            now = node[now]
        if c % 2: # If cycle length is odd
            k += 1
    
    # k = number of odd cycles
    # We want to minimize the number of odd cycles because they force same-value assignments
    # So we aim to use (n - k) // 2 pairs to maximize the result
    k = (n - k) // 2
    
    ans = 0
    
    # Subtract twice the smallest k values (since we're pairing them)
    for i in range(1, k + 1):
        ans -= 2 * i
    
    # Add twice the largest k values
    for i in range(n, n - k, -1):
        ans += 2 * i
    
    print(ans)


# https://github.com/VaHiX/CodeForces/