# Problem: CF 2167 F - Tree, TREE!!!
# https://codeforces.com/contest/2167/problem/F

"""
Algorithm: Tree DFS + LCA Counting
Time Complexity: O(n)
Space Complexity: O(n)

This code computes the kawaiiness of a tree, defined as the sum over all possible roots r
of the number of distinct LCA values obtained from all possible sets of k nodes in the tree.

The approach:
1. Build adjacency list representation of the tree.
2. Perform DFS to compute subtree sizes and parent relationships.
3. For each node as root, count how many distinct LCAs can be obtained by choosing k nodes.
4. Use the fact that for a node u in a tree with root r, if we select k nodes, 
   the LCA of those k nodes will be u if and only if u is the deepest node such that
   at least k of the k chosen nodes are in the subtree rooted at u. This leads to 
   counting contributions based on subtree sizes.
5. Efficiently compute for each node the number of valid sets of k nodes where 
   the LCA is that node.

The key insight is to count, for each node, the number of k-subsets of nodes such 
that this node is their LCA. This is done using subtree sizes and the fact that:
- If we fix a node v as LCA of k nodes, then those k nodes must be chosen such that
  they are distributed over the subtrees of v's children, and we want at least one from each.
- But since we're counting over all possible sets, we compute how many such sets 
  lead to LCA equal to v.
"""

import sys
from array import array

input = sys.stdin.readline


def solve():
    T = int(input())
    for _ in range(T):
        n, k = map(int, input().split())
        m = n - 1
        deg = [0] * (n + 1)
        U = [0] * m
        V = [0] * m
        for i in range(m):
            u, v = map(int, input().split())
            U[i] = u
            V[i] = v
            deg[u] += 1
            deg[v] += 1
        start = array("I", [0]) * (n + 2)
        s = 0
        for u in range(1, n + 1):
            start[u] = s
            s += deg[u]
        start[n + 1] = s
        adj = array("I", [0]) * (2 * m)
        ptr = start.tolist()
        for i in range(m):
            u, v = U[i], V[i]
            adj[ptr[u]] = v
            ptr[u] += 1
            adj[ptr[v]] = u
            ptr[v] += 1
        U = V = ptr = None

        parent = array("i", [-1]) * (n + 1)
        sz = array("I", [1]) * (n + 1)
        stack = [(1, 0)]
        parent[1] = -2
        while stack:
            u, stage = stack.pop()
            if stage == 0:
                stack.append((u, 1))
                i0, i1 = start[u], start[u + 1]
                for i in range(i0, i1):
                    v = adj[i]
                    if v != parent[u]:
                        parent[v] = u
                        stack.append((v, 0))
            else:
                i0, i1 = start[u], start[u + 1]
                szu = 1
                for i in range(i0, i1):
                    v = adj[i]
                    if v != parent[u]:
                        szu += sz[v]
                sz[u] = szu

        ans = 0
        for v in range(1, n + 1):
            cnt = 1  # At least one set is the singleton {v}
            i0, i1 = start[v], start[v + 1]
            pv = parent[v]
            for i in range(i0, i1):
                u = adj[i]
                a = sz[v] if u == pv else (n - sz[u])
                if a >= k:
                    cnt += n - a  # Number of valid selections that include this edge
            ans += cnt
        print(ans)


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/