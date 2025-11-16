# Problem: CF 2139 E1 - Maple and Tree Beauty (Easy Version)
# https://codeforces.com/contest/2139/problem/E1

"""
E1. Maple and Tree Beauty (Easy Version)

This problem involves a rooted tree where each node must be labeled with either 0 or 1,
with exactly k zeros and (n - k) ones. The goal is to maximize the length of the longest
common subsequence (LCS) among all leaf nodes' "names" — strings formed by concatenating
node labels from root to that node.

The algorithm builds a tree from input, traverses level-by-level to track number of leaves
at each depth. It then attempts to distribute k zeros optimally across levels to maximize
the LCS of leaf names.

Key idea:
- First determine the maximum number of layers possible (tree height)
- Use dynamic programming with bitmasks (dp) to check combinations of how many 0s
  to place in each layer so that total 0s equals k and both k and (n-k) constraints are respected
- If we cannot satisfy constraint using all layers, reduce the layer count until feasible

Time Complexity: O(n^2 + 2^n)
Space Complexity: O(n)

Algorithms/Techniques:
- Tree building from parent array
- BFS-like traversal to identify layer structure
- Bitmask dynamic programming for subset sum matching
"""

import sys

input = lambda: sys.stdin.readline().rstrip()
ii = lambda: int(input())
mii = lambda: map(int, input().split())
lii = lambda: list(mii())


def solve():
    n, k = mii()
    g = [[] for _ in range(n)]
    # Build the tree from parent information
    for v, u in enumerate(mii(), 1):
        g[u - 1].append(v)
    
    layers = [1]  # Start with root layer (1 node)
    q = [0]       # Queue of nodes at current level (starting with root)
    flag = True   # Check if tree is valid; stop traversal if any node has no children
    
    while q and flag:
        tmp = []
        for u in q:
            if not g[u]:  # If current node is a leaf
                flag = False
                break
            tmp.extend(g[u])  # Add children to next level
        if flag:
            layers.append(len(tmp))  # Record number of nodes at this level
            q = tmp                  # Move to next level
    
    tot = sum(layers)  # Total number of leaves in the full tree
    if tot <= max(k, n - k):  # Early return condition: impossible to use more than needed
        return len(layers)
    
    # dp will be used as a bitmask where dp[i] indicates whether we can achieve i zeros
    dp = 1  # Initially only 0 zeros are used
    
    # Update the mask for all possible sums of layers
    for x in layers:
        dp |= dp << x  # Shift and OR to include new combinations
    
    # Check each possible number of zeros that fits within constraints
    for i in range(tot + 1):
        if dp & 1:  # If such combination is valid
            if i <= k and tot - i <= n - k:
                return len(layers)
        dp >>= 1  # Move to check next value
    
    # If we cannot fully satisfy all constraints even with all layers, try fewer layers
    return len(layers) - 1


for _ in range(ii()):
    print(solve())


# https://github.com/VaHiX/codeForces/