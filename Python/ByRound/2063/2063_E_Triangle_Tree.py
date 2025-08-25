# Contest 2063, Problem E: Triangle Tree
# URL: https://codeforces.com/contest/2063/problem/E

# https://codeforces.com/contest/2063

import sys

input = lambda: sys.stdin.readline().rstrip()  # faster!


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
        self._edges.append(node1)
        self._edges.append(node2)

    def adj_itr(self, node):
        for i in range(self._s[node], self._s[node + 1]):
            yield self._g[i]

    def adj_idx(self, node, idx):
        return self._g[self._s[node] + idx]

    def len_adj(self, node):
        return self._s[node + 1] - self._s[node]

    def build(self, root: int):
        # first build adjacency
        for i in self._edges:
            self._s[i + 2] += 1
        for i in range(self.n + 1):
            self._s[i + 1] += self._s[i]
        self._g = [0] * len(self._edges)
        for i in range(len(self._edges)):
            j = self._edges[i] + 1
            self._g[self._s[j]] = self._edges[i ^ 1]
            self._s[j] += 1
        # then build tree
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
        if node == self.root:
            return self.len_adj(node) == 0
        else:
            return self.len_adj(node) == 1

    def is_root(self, node: int) -> bool:
        return node == self.root

    def children(self, node: int):
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
    for u in reversed(tree.bfs_tour):
        n_depth[tree.node_depth[u]] += 1
        if not tree.is_root(u):
            subtree_size[tree.parent[u]] += subtree_size[u]

    n_depth_pref = [0] * (max_depth + 2)
    for d in range(max_depth + 1):
        n_depth_pref[d + 1] = n_depth_pref[d] + n_depth[d]

    ans = 0
    for u in range(n):
        k = (
            n_depth_pref[max_depth + 1]
            - n_depth_pref[tree.node_depth[u]]
            - subtree_size[u]
        )
        ans += 2 * tree.node_depth[u] * k
    for d in range(max_depth + 1):
        ans -= d * n_depth[d] * (n_depth[d] - 1)
    for u in range(n):
        pairs = 0
        for v in tree.children(u):
            pairs += subtree_size[v] * (subtree_size[u] - 1 - subtree_size[v])
        pairs //= 2
        ans -= (2 * tree.node_depth[u] + 1) * pairs
    return ans


ans = []
for _ in range(int(input())):
    ans += [str(solve_case())]
print("\n".join(ans))
