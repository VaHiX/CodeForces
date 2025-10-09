# Problem: CF 2127 E - Ancient Tree
# https://codeforces.com/contest/2127/problem/E

"""
E. Ancient Tree

Algorithm:
This problem involves rooting a tree and performing dynamic programming on it to assign colors 
to nodes such that the total weight of "cutie" nodes is minimized.

Key Techniques:
1. Tree representation using adjacency lists (with efficient traversal)
2. BFS-based tree traversal for processing nodes in bottom-up order
3. Dynamic Programming with set operations to track color conflicts at each node
4. Efficient color assignment based on lowest common ancestor (LCA) properties

Time Complexity: O(n * k)
Space Complexity: O(n + k)

The solution uses a greedy approach where for each node, it considers its children and 
merges their conflict sets to determine whether the current node becomes cutie or not.
"""

import sys

input = lambda: sys.stdin.readline().rstrip()


class Tree:
    def __init__(self, n: int):
        self.n = n
        self.root = -1
        self.depth = -1
        self.parent = [-1] * n
        self.node_depth = [-1] * n
        self.bfs_tour = []
        self._edges = []
        self._s = [0] * (n + 2)
        self._g = []

    def add_edge(self, node1: int, node2: int):
        # Add edges to internal edge list for building adjacency list structure
        self._edges.append(node1)
        self._edges.append(node2)

    def adj_itr(self, node):
        # Iterate over neighbors of a node
        for i in range(self._s[node], self._s[node + 1]):
            yield self._g[i]

    def adj_idx(self, node, idx):
        # Get neighbor at specific index
        return self._g[self._s[node] + idx]

    def len_adj(self, node):
        # Length of adjacency list for a node
        return self._s[node + 1] - self._s[node]

    def build(self, root: int):
        # Build the adjacency list from edge list using a technique similar to 
        # adjacency list construction with counting sort-like behavior
        
        # Count degrees of each node (shifted by 2 for indexing)
        for i in self._edges:
            self._s[i + 2] += 1
        # Prefix sum to get starting positions of edges for each node
        for i in range(self.n + 1):
            self._s[i + 1] += self._s[i]
        # Fill adjacency list
        self._g = [0] * len(self._edges)
        for i in range(len(self._edges)):
            j = self._edges[i] + 1
            self._g[self._s[j]] = self._edges[i ^ 1]  # XOR with 1 to get the other endpoint
            self._s[j] += 1
        
        # Perform BFS traversal starting from root
        self.root = root
        self.parent[root] = -1  # Root has no parent
        self.node_depth[root] = 0  # Root depth is 0
        self.bfs_tour = [root]
        
        for v in self.bfs_tour:  # Traverse BFS order
            for u in self.adj_itr(v):  # Visit all neighbors
                if u != self.parent[v]:  # Skip parent (to avoid going up the tree)
                    self.parent[u] = v  # Record parent relationship
                    self.node_depth[u] = self.node_depth[v] + 1  # Set depth
                    self.bfs_tour += [u]  # Add to BFS tour
        self.depth = self.node_depth[self.bfs_tour[-1]]  # Last node's depth gives max depth

    def is_leaf(self, node: int) -> bool:
        # Check if a node is a leaf (has no children with different parent)
        if node == self.root:
            return self.len_adj(node) == 0
        else:
            return self.len_adj(node) == 1

    def is_root(self, node: int) -> bool:
        # Check if node is root
        return node == self.root

    def children(self, node: int):
        # Yield all children (neighbors except parent)
        for neighbour in self.adj_itr(node):
            if neighbour != self.parent[node]:
                yield neighbour


def solve_case():
    n, k = map(int, input().split())
    w = list(map(int, input().split()))
    c = list(map(int, input().split()))
    tree = Tree(n)  # Create new tree
    for _ in range(n - 1):
        u, v = map(lambda x: int(x) - 1, input().split())  # Convert to 0-indexed
        tree.add_edge(u, v)
    tree.build(0)  # Build tree rooted at node 0
    ans = 0
    s = [set() for _ in range(n)]  # Sets to store conflicting colors for each node
    
    # Process nodes from bottom-up (reverse BFS order)
    for u in reversed(tree.bfs_tour):
        d = set()  # Set to store conflicts between children's sets
        
        # For each child
        for v in tree.children(u):
            # Swap sets to have smaller set on left for efficiency (merge small into large)
            if len(s[u]) < len(s[v]):
                s[u], s[v] = s[v], s[u]
            
            # Check for color conflicts between s[u] and s[v]
            for x in s[v]:
                if x in s[u]:
                    d.add(x)  # If present in both sets, it's a conflict
                else:
                    s[u].add(x)  # Otherwise add to main set
        
        # Handle coloring logic
        if c[u] == 0:  # Node u has lost color (needs assignment)
            if len(d) >= 2:  # More than one conflicting color -> node is cutie
                ans += w[u]
            if len(d) >= 1:  # At least one conflict exists
                # Pick the first conflicting color as new color (greedy choice)
                c[u] = next(iter(d))  
        else:
            # Node u already had a color but check for conflicts with children's sets
            if len(d) >= 2:
                ans += w[u]
            elif len(d) == 1 and c[u] != next(iter(d)):  # One conflict, but color differs
                ans += w[u]  
            s[u].add(c[u])  # Add current color to set
    
    # Final pass to assign default colors where necessary
    for u in tree.bfs_tour:
        if c[u] == 0:
            c[u] = 1 if u == 0 else c[tree.parent[u]]
    
    return f"{ans}\n{' '.join(map(str, c))}"


ans = []
for _ in range(int(input())):
    ans.append(str(solve_case()))
print("\n".join(ans))


# https://github.com/VaHiX/codeForces/