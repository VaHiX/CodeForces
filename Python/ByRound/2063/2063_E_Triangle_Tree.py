# Problem: CF 2063 E - Triangle Tree
# https://codeforces.com/contest/2063/problem/E

"""
E. Triangle Tree

Purpose:
    This code solves a problem involving a rooted tree where we need to compute the sum of function f(u, v) over all pairs (u, v) with u < v.
    
    Function f(u,v):
        - If (u,v) is a good pair (i.e., neither u is ancestor of v nor v is ancestor of u), then:
            * Let dist(u,lca(u,v)) = a, dist(v,lca(u,v)) = b
            * Count the number of distinct integer values x such that triangle with sides a, b, x exists.
        - Otherwise (if one is ancestor of the other), f(u,v) = 0

Algorithms & Techniques:
    - Tree traversal using BFS to compute parent and depth information
    - Subtree sizes and prefix sums for efficient computation
    - Mathematical computation based on triangle inequality constraints:
        * For two sides a and b, valid values of x must satisfy: |a-b| < x < a+b
        * Count valid integer x values in that range

Time Complexity:
    O(n) per test case where n is the number of nodes.
    Construction of adjacency list, BFS traversal, and computation all linear in n.

Space Complexity:
    O(n) for storing tree structures, BFS tour, node depths, subtrees, etc.
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
        # Add bidirectional edge representation for adjacency list
        self._edges.append(node1)
        self._edges.append(node2)

    def adj_itr(self, node):
        # Iterate over neighbors of a node
        for i in range(self._s[node], self._s[node + 1]):
            yield self._g[i]

    def adj_idx(self, node, idx):
        # Return neighbor at given index
        return self._g[self._s[node] + idx]

    def len_adj(self, node):
        # Return number of neighbors for a node
        return self._s[node + 1] - self._s[node]

    def build(self, root: int):
        # Build adjacency list from edge list using implicit array indexing
        for i in self._edges:
            self._s[i + 2] += 1
        for i in range(self.n + 1):
            self._s[i + 1] += self._s[i]
        self._g = [0] * len(self._edges)
        for i in range(len(self._edges)):
            j = self._edges[i] + 1
            self._g[self._s[j]] = self._edges[i ^ 1]
            self._s[j] += 1

        # Do BFS to compute parent and depth for each node
        self.root = root
        self.parent[root] = -1
        self.node_depth[root] = 0
        self.bfs_tour = [root]
        for v in self.bfs_tour:
            for u in self.adj_itr(v):
                if u != self.parent[v]:
                    self.parent[u] = v
                    self.node_depth[u] = self.node_depth[v] + 1
                    self.bfs_tour += [u]
        self.depth = self.node_depth[self.bfs_tour[-1]]

    def is_leaf(self, node: int) -> bool:
        # Return True if node is leaf (has no children)
        if node == self.root:
            return self.len_adj(node) == 0
        else:
            return self.len_adj(node) == 1

    def is_root(self, node: int) -> bool:
        # Return True if node is root
        return node == self.root

    def children(self, node: int):
        # Yield all children of a node (neighbours excluding parent)
        for neighbour in self.adj_itr(node):
            if neighbour != self.parent[node]:
                yield neighbour


def solve_case():
    n = int(input())
    tree = Tree(n)
    for _ in range(n - 1):
        u, v = map(lambda x: int(x) - 1, input().split())
        tree.add_edge(u, v)
    tree.build(0)
    max_depth = tree.depth
    n_depth = [0] * (max_depth + 1)
    subtree_size = [1] * n
    
    # Count number of nodes at each depth and compute subtree sizes via reverse BFS
    for u in reversed(tree.bfs_tour):
        n_depth[tree.node_depth[u]] += 1
        if not tree.is_root(u):
            subtree_size[tree.parent[u]] += subtree_size[u]
    
    # Build prefix sum of nodes per depth level (used later in computation)
    n_depth_pref = [0] * (max_depth + 2)
    for d in range(max_depth + 1):
        n_depth_pref[d + 1] = n_depth_pref[d] + n_depth[d]

    ans = 0
    
    # Compute total contribution of each node using formula involving subtree size and depth
    for u in range(n):
        # Number of nodes at higher levels than current node's level
        k = (
            n_depth_pref[max_depth + 1]
            - n_depth_pref[tree.node_depth[u]]
            - subtree_size[u]  # Remove itself and its subtree from count
        )
        ans += 2 * tree.node_depth[u] * k
    
    # Subtract invalid triangle combinations due to same depth counts
    for d in range(max_depth + 1):
        ans -= d * n_depth[d] * (n_depth[d] - 1)
    
    # Apply correction for child-parent pairs using subtree sizes
    for u in range(n):
        pairs = 0
        for v in tree.children(u):
            pairs += subtree_size[v] * (subtree_size[u] - 1 - subtree_size[v])  # Count valid internal combinations
        pairs //= 2  # Count half to avoid double counting
        ans -= (2 * tree.node_depth[u] + 1) * pairs
    
    return ans


ans = []
for _ in range(int(input())):
    ans += [str(solve_case())]
print("\n".join(ans))


# https://github.com/VaHiX/codeForces/