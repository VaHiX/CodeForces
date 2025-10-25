# Problem: CF 2031 E - Penchick and Chloe's Trees
# https://codeforces.com/contest/2031/problem/E

"""
E. Penchick and Chloe's Trees
Algorithm: Dynamic Programming on Tree with Bit Manipulation
Time Complexity: O(n log n) per test case due to sorting and processing each node once
Space Complexity: O(n) for storing tree structure, depths, and answer values

This problem involves finding the minimum depth of a perfect binary tree that is isomorphic 
to a given rooted tree. The key idea is to use dynamic programming on the tree, where for 
each node, we compute the "cost" (in terms of depth) required to match its subtree structure
to a perfect binary tree. The approach uses bit manipulation and careful merging of child
subtrees.

Key techniques:
- Tree representation using parent array
- Depth-first traversal from leaves up
- Sorting children by their computed values to process in order
- Bit manipulation for efficient computation of minimal depth needed
"""

for _ in range(int(input())):
    n = int(input())
    par = [0] + [int(t) - 1 for t in input().split()]
    child = [[] for _ in range(n)]
    for i in range(1, n):
        child[par[i]].append(i)
    
    # Compute depth of each node
    depth = [0] * n
    for i in range(1, n):
        depth[i] = depth[par[i]] + 1
    
    ans = [0] * n
    # Traverse nodes from leaves to root (bottom-up DP)
    for i in range(n - 1, -1, -1):
        if not child[i]:
            # Leaf node has no cost to match itself
            ans[i] = 0
            continue
        if len(child[i]) == 1:
            # Single child: cost is 1 more than child's cost
            ans[i] = 1 + ans[child[i][0]]
            continue
        
        # Multiple children: need to merge their contributions
        bitz = sorted(ans[j] for j in child[i])  # Sort children by their costs
        cur = 0  # Current bits used
        v = 0    # Current depth offset
        for t in bitz:
            if v < t:
                # Adjust current bit usage based on gap between depths
                d = t - v
                cur = (cur - 1) >> d  # Shift bits right by gap
                cur += 1              # Account for new bit
            cur += 1  # Add current child's contribution
            v = t     # Update current depth
        
        # Final result for node i is calculated from total bit usage and depth
        ans[i] = v + (cur - 1).bit_length()
    print(ans[0])


# https://github.com/VaHiX/codeForces/