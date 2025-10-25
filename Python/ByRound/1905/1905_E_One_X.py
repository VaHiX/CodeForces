# Problem: CF 1905 E - One-X
# https://codeforces.com/contest/1905/problem/E

"""
Algorithm: 
Dynamic Programming with Memoization on Segment Tree Structure
The problem involves computing the sum of least common ancestors (LCAs) for all non-empty subsets of leaves in a segment tree.

Key Insight:
- For a segment tree built from an array of size n, the leaves are nodes from n to 2*n - 1.
- Each node u has two children: 2*u and 2*u + 1.
- The LCA of a subset of leaves can be computed efficiently using recursive structure of segment tree.
- The recurrence uses memoization to avoid recomputation.

Time Complexity: O(log n) per test case due to depth of recursion and memoization.
Space Complexity: O(log n) for recursion stack and memoization cache.

Approach:
- Use DFS with memoization to compute for each node u the sum of LCAs of all subsets of leaves in its subtree.
- The recursion builds up the solution by combining results from left and right subtrees.
- For a node u, we compute (a0, a1, a2) where:
  - a0: sum of LCAs of all subsets involving leaves in subtree
  - a1: auxiliary value used in computation
  - a2: number of nodes in subtree
"""

import sys
from functools import lru_cache

M = 998244353
it = iter(map(int, sys.stdin.buffer.read().split()))
t = next(it)
out = []


@lru_cache(None)
def dfs(u):
    # Base case: if u == 1, it's root, return base values
    if u == 1:
        return (1, 0, 2)
    # Calculate parent node index
    r = u >> 1
    # Recursive calls on left and right subtrees of u
    t1 = dfs(u - r)
    t2 = dfs(r)
    # Combine results recursively:
    # a0: Total sum of LCAs for current subtree
    # a1: Auxiliary sum used in computation
    # a2: Number of nodes in subtree
    a0 = ((t1[0] + t2[0]) * 2 + (t1[2] - 1) * (t2[2] - 1)) % M
    a1 = (t1[1] + t2[1] + t2[0]) % M
    a2 = (t1[2] * t2[2]) % M
    return (a0, a1, a2)


for _ in range(t):
    n = next(it)
    a0, a1, _ = dfs(n)
    out.append(str((a0 + a1) % M))
sys.stdout.write("\n".join(out))


# https://github.com/VaHiX/CodeForces/