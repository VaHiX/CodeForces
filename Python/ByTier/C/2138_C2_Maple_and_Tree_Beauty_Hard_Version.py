# Problem: CF 2138 C2 - Maple and Tree Beauty (Hard Version)
# https://codeforces.com/contest/2138/problem/C2

"""
C2. Maple and Tree Beauty (Hard Version)

Purpose:
This code solves a problem where we are given a rooted tree with n nodes and must assign labels 
(0 or 1) to each node such that exactly k nodes are labeled 0, and the remaining are labeled 1. 
The goal is to maximize the length of the longest common subsequence (LCS) of all leaf node names.
Each node's name is defined as the binary string formed by concatenating labels along the path from the root.

Approach:
- Build a tree from parent information.
- Traverse the tree level by level (BFS-style).
- For each level, count how many children exist at that level.
- The key idea is to compute what can be maximized using the counts of nodes at each level.
- Use bit manipulation to simulate and calculate the maximum possible LCS.

Algorithms/Techniques:
- Tree construction from parent list
- BFS traversal of tree
- Counting nodes per level and tracking subtree structures
- Bit manipulation for optimization

Time Complexity: O(n)
Space Complexity: O(n)

Input format:
- First line: number of test cases t
- For each case:
  - n and k (number of nodes, number of zeros)
  - Parent list of n-1 elements indicating parent of each node from 2 to n

Output:
- Maximum beauty over all valid labelings.
"""

import sys

input = lambda: sys.stdin.readline().rstrip()
ii = lambda: int(input())
mii = lambda: map(int, input().split())
lii = lambda: list(mii())
from collections import defaultdict


def solve():
    n, k = mii()  # Read number of nodes and zeros
    g = [[] for _ in range(n)]  # Build adjacency list representation of tree
    parents = mii()
    for v, u in enumerate(parents, 1):  # Process parent information
        g[u - 1].append(v)  # Connect parent to child
    
    cnt = defaultdict(int)  # Count number of children at each level
    cnt[1] = 1  # Root has one node (starting point)
    q = [0]  # BFS queue, root is index 0
    flag = True  # Flag to detect if we can continue the traversal
    
    while q and flag:
        tmp = []  # Temporary list to store next level nodes
        for u in q:  # For each node in current level
            if not g[u]:  # If this node is a leaf
                flag = False  # Stop processing since no more children
                break
            tmp.extend(g[u])  # Add all children to the next level
        if flag:
            cnt[len(tmp)] += 1  # Count how many nodes are present at this level
            q = tmp  # Move to next level
    
    mx = sum(cnt.values())  # Total number of levels in the BFS tree
    tot = sum(x * c for x, c in cnt.items())  # Total number of nodes in the tree
    
    if tot <= k or tot <= n - k:  # Early exit if total less than allowed number of zeroes or ones
        return mx
    
    f = 1  # Bitmask to simulate possible subsequences
    for x, c in cnt.items():  # Process each count group
        for b in range(c.bit_length() - 1):  # Iterate through bit lengths
            f |= f << (x << b)  # Shift and OR with previous result
        rem = c + 1 - (1 << (c.bit_length() - 1))  # Calculate remaining bits needed
        if rem:
            f |= f << (x * rem)  # Include remaining portion
    f &= (1 << (k + 1)) - 1  # Limit based on k
    f >>= tot - n + k  # Adjust shifting to get final result
    
    return mx if f else mx - 1  # Return adjusted maximum depending on final bitmask


for _ in range(ii()):
    print(solve())


# https://github.com/VaHiX/codeForces/