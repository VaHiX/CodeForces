# Problem: CF 1740 E - Hanging Hearts
# https://codeforces.com/contest/1740/problem/E

"""
Algorithm: Tree Dynamic Programming with Greedy Strategy
Time Complexity: O(n)
Space Complexity: O(n)

This problem involves a tree structure where each node (card) can be processed in a specific order, 
and during processing, values can be updated to maintain a non-decreasing subsequence. 
The approach uses a post-order traversal on the tree to compute optimal values for each node.
We calculate for each node:
1. The maximum depth of its subtree (used for determining how many updates can occur).
2. The best possible contribution to the final non-decreasing sequence from that node's subtree.
The root node's best value represents the maximum length of the longest non-decreasing subsequence.

Key variables:
- depth[i]: maximum depth of subtree rooted at node i
- best[i]: maximum contribution to longest non-decreasing subsequence from subtree rooted at node i
"""

import sys

n = int(input())
a = [int(x) - 1 for x in sys.stdin.readline().split()]  # Convert to 0-indexed
depth = [1] * n  # Initialize depth array with 1 for each node
best = [0] * n   # Initialize best array to track contribution from each node

# Traverse nodes in reverse order (from leaves to root) - post-order traversal
for i in range(n - 1, -1, -1):
    # Update best value at current node with its depth
    best[i] = max(best[i], depth[i])
    
    # If current node is not the root, update its parent's information
    if i != 0:
        parent = a[i - 1]  # Get parent node (a[i-1] is 0-indexed parent of node i)
        # Update parent's depth based on current node's depth
        depth[parent] = max(depth[parent], 1 + depth[i])
        # Accumulate best values from current node to parent
        best[parent] += best[i]

# Output the maximum possible length of longest non-decreasing subsequence
print(best[0])


# https://github.com/VaHiX/CodeForces/