# Problem: CF 1856 E1 - PermuTree (easy version)
# https://codeforces.com/contest/1856/problem/E1

"""
Algorithm: PermuTree (Easy Version)
Purpose: Given a rooted tree, assign values 1..n to nodes to maximize the number of pairs (u,v) such that 
         a_u < a_lca(u,v) < a_v. This is solved by dynamic programming on tree with bitmask optimization.

Approach:
- Build the tree from parent array
- Perform post-order DFS to compute subtree sizes
- For each non-leaf node, compute optimal assignment of values to children's subtrees
  to maximize the count of valid pairs (u,v) with u in one subtree and v in another
- Use bitmask to track which value assignments are possible in each subtree
- For each node, split the children's subsizes into two parts and compute max product

Time Complexity: O(n^2) in worst case due to iterative computation and bitmask operations,
                 but optimized via dynamic programming on trees
Space Complexity: O(n) for storing tree structure, subtree sizes, and order

Note: The solution uses a greedy-like approach to assign values to maximize the number of valid pairs
      by leveraging properties of how tree traversal affects LCA relationships.
"""

import sys

sys.setrecursionlimit(1 << 25)


def main():
    data = list(map(int, sys.stdin.buffer.read().split()))
    it = iter(data)
    n = next(it)
    parent = [0] * (n + 1)
    parent[1] = 0
    for v in range(2, n + 1):
        parent[v] = next(it)
    children = [[] for _ in range(n + 1)]
    for v in range(2, n + 1):
        children[parent[v]].append(v)
    size = [0] * (n + 1)
    order = []
    stack = [(1, 0)]
    while stack:
        v, st = stack.pop()
        if st == 0:
            stack.append((v, 1))
            for u in children[v]:
                stack.append((u, 0))
        else:
            s = 1
            for u in children[v]:
                s += size[u]
            size[v] = s
            order.append(v)
    ans = 0
    for v in range(1, n + 1):
        if not children[v]:
            continue
        parts = [size[u] for u in children[v]]
        S = sum(parts)
        mask = 1
        for s in parts:
            mask |= mask << s
        mid = S // 2
        lower_mask = mask & ((1 << (mid + 1)) - 1)
        if lower_mask:
            x1 = lower_mask.bit_length() - 1
            best = x1 * (S - x1)
        else:
            best = 0
        if mid + 1 <= S:
            upper = mask >> (mid + 1)
            if upper:
                lowbit = upper & -upper
                x2 = (mid + 1) + (lowbit.bit_length() - 1)
                cand = x2 * (S - x2)
                if cand > best:
                    best = cand
        ans += best
    print(ans)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/