# Problem: CF 1689 C - Infected Tree
# https://codeforces.com/contest/1689/problem/C

# ====================================================================
# Algorithm: Tree Traversal with BFS
# Approach: 
#   - Perform BFS starting from root (vertex 1)
#   - For each node, track its depth and whether it's already visited
#   - At each node, if it has fewer than 2 children (excluding parent), 
#     update best depth and number of children
#   - The answer is calculated as: n - 2 * best - 1 - kids
# Time Complexity: O(n) - Each node is visited once in BFS
# Space Complexity: O(n) - For adjacency list, visited set, and queue
# ====================================================================

import sys
from collections import defaultdict, deque

input = sys.stdin.buffer.readline
for _ in range(int(input())):
    n = int(input())
    d = defaultdict(list)
    for _ in range(n - 1):
        a, b = map(int, input().split())
        d[a].append(b)
        d[b].append(a)
    q = deque([(0, 1)])  # Queue holds (depth, node_id)
    vis = set()
    best = float("inf")  # Minimum depth where we have < 2 children
    kids = float("inf")  # Minimum number of children at that depth
    while q:
        dep, ind = q.popleft()
        if dep > best:  # Early termination if beyond best depth
            break
        if ind not in vis:
            vis.add(ind)
            # Count children (excluding parent)
            # (dep > 0) accounts for the fact that root has no parent
            child_count = len(d[ind]) - (dep > 0)  
            if child_count < 2:
                best = dep
                kids = min(child_count, kids)
            for v in d[ind]:
                if v not in vis:
                    q.append((dep + 1, v))
    # Calculate maximum number of vertices that can be saved
    # n - 2 * best - 1 - kids
    print(n - 2 * best - 1 - kids)


# https://github.com/VaHiX/CodeForces/