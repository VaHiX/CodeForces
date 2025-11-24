# Problem: CF 930 A - Peculiar apple-tree
# https://codeforces.com/contest/930/problem/A

"""
Algorithm: Tree Depth Analysis with Modular Arithmetic

This solution models the apple rolling process on a tree structure:
1. Each inflorescence has a parent (except root)
2. Apples roll down from each inflorescence to its parent 
3. Apples in same inflorescence annihilate in pairs (mod 2 operation)
4. We track depth of each node to determine how many apples reach the root

Time Complexity: O(n)
Space Complexity: O(n)

Approach:
- Compute depth of each node from root (depth 0)
- For each depth level, count number of nodes (inflorescences)
- Apply modulo 2 to simulate pair-wise annihilation of apples
- Sum remaining apples at root level (depth 0)
"""

import sys

input = sys.stdin.buffer.readline


def process(n, A):
    # Initialize depth array to store depth of each inflorescence
    depth = [0 for i in range(n + 1)]
    depth[1] = 0  # Root has depth 0
    
    # Calculate depth for each inflorescence by traversing up the tree
    for i in range(2, n + 1):
        pi = A[i - 2]  # Parent of i-th inflorescence
        depth[i] = depth[pi] + 1  # Depth is parent's depth + 1
    
    # Dictionary to count inflorescences at each depth level
    d = {}
    for i in range(1, n + 1):
        x = depth[i]  # Depth of current inflorescence
        if x not in d:
            d[x] = 0
        # Modulo 2 operation simulates annihilation of pairs
        d[x] = (d[x] + 1) % 2
    
    # Sum up remaining apples at root level (depth 0)
    return sum(d.values())


n = int(input())
A = [int(x) for x in input().split()]
print(process(n, A))


# https://github.com/VaHiX/CodeForces/