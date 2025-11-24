# Problem: CF 1702 G2 - Passable Paths (hard version)
# https://codeforces.com/contest/1702/problem/G2

"""
Algorithm: Tree Path Passability Check using LCA (Lowest Common Ancestor)
Time Complexity: O(n log n + q * k log n) where n is number of nodes, q is number of queries, k is average query size
Space Complexity: O(n log n)

This solution determines if a set of vertices in a tree forms a passable path.
A set is passable if there exists a simple path in the tree that visits all vertices in the set.
The key insight is that a set of vertices is passable if and only if:
1. All vertices can be connected by a single path (i.e., the vertices form a connected subtree)
2. The path can be represented as a simple path from one vertex to another in the tree
3. This is true if and only if the LCA of the deepest vertex and the deepest of the remaining vertices satisfies certain conditions

The approach:
1. Preprocess the tree to build LCA structure using binary lifting
2. For each query:
   - Sort vertices by depth in descending order
   - Use LCA to check connectivity conditions
   - Verify that vertices form a valid path in the tree
"""

import sys


class LCA:
    def __init__(self, g, root=0):
        self.g = g
        self.root = root
        self.n = len(g)
        self.logn = (self.n - 1).bit_length()  # Number of bits needed to represent n-1
        self.depth = [-1] * self.n  # Depth of each node
        self.parent = [[-1] * self.logn for _ in range(self.n)]  # Parent table for binary lifting
        self._dfs()  # Compute depths and first parents
        self._doubling()  # Precompute parent table for binary lifting

    def _dfs(self):
        # Perform DFS to compute depths and first parents
        self.depth[self.root] = 0
        stack = [self.root]
        while stack:
            u = stack.pop()
            for v in self.g[u]:
                if self.depth[v] == -1:  # If not visited yet
                    self.depth[v] = self.depth[u] + 1
                    self.parent[v][0] = u  # Set first parent
                    stack.append(v)

    def _doubling(self):
        # Fill parent table using binary lifting
        for i in range(self.logn - 1):
            for p in self.parent:
                if p[i] != -1:  # If parent exists
                    p[i + 1] = self.parent[p[i]][i]  # Set 2^i-th parent

    def lca(self, u, v):
        # Find lowest common ancestor of u and v
        if self.depth[v] < self.depth[u]:
            u, v = v, u  # Make u deeper than v
        d = self.depth[v] - self.depth[u]
        # Bring v to same depth as u using binary lifting
        for i in range(d.bit_length()):
            if d >> i & 1:
                v = self.parent[v][i]
        if u == v:
            return u
        # Move both up until they meet
        for i in reversed(range(self.logn)):
            if (pu := self.parent[u][i]) != (pv := self.parent[v][i]):
                u, v = pu, pv
        return self.parent[u][i]


def query():
    # Read query
    k = int(sys.stdin.readline())
    p = sorted(
        (int(x) - 1 for x in sys.stdin.readline().split()),  # Convert to 0-indexed
        key=lca.depth.__getitem__,  # Sort by depth (descending)
        reverse=True,
    )
    
    # Track vertices that are "branching points" in the path
    b = []
    r = p[0]  # Start with deepest vertex
    
    # Process vertices from deepest to shallowest to detect branching
    for x in p[1:]:
        if lca.lca(r, x) == x:  # If x is ancestor of r
            r = x  # Set x as new ancestor
        else:
            b.append(x)  # Add to branching points
    
    # If no branching points, the path is valid
    if not b:
        return True
    
    # Check if branching points are properly connected to the main path
    if not lca.lca(b[0], p[0]) == lca.lca(b[0], r):
        return False
    
    # Check if all branching points form a valid sequence
    for i in range(len(b) - 1):
        if lca.lca(b[i], b[i + 1]) != b[i + 1]:
            return False
    
    return True


# Read input tree
n = int(input())
g = [[] for _ in range(n)]
for _ in range(n - 1):
    u, v = (int(x) - 1 for x in sys.stdin.readline().split())
    g[u].append(v)
    g[v].append(u)

# Build LCA structure
lca = LCA(g)

# Process queries
for _ in range(int(input())):
    print("YES" if query() else "NO")


# https://github.com/VaHiX/CodeForces/