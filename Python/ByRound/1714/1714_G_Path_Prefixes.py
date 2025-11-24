# Problem: CF 1714 G - Path Prefixes
# https://codeforces.com/contest/1714/problem/G

"""
Algorithm: Tree Traversal with Prefix Sum and Binary Search
Techniques: DFS traversal, prefix sum computation, binary search for maximum prefix

Time Complexity: O(n * log(n)) per test case, where n is the number of vertices.
Space Complexity: O(n) for storing the tree structure, prefix sums, and stack.

This solution processes each node in a depth-first search manner. For each node,
it computes the prefix sums of 'b' values along the path from root to current node.
Then, for each node, it finds the longest prefix of the path (in terms of number of edges)
such that the sum of 'b' values does not exceed the total sum of 'a' values up to that point.
Binary search is used to efficiently find this prefix.
"""

from bisect import bisect as br

R, G = lambda: map(int, input().split()), range
(t,) = R()
for _ in G(t):
    (n,) = R()
    g = [[] for _ in G(n)]
    for i in G(1, n):
        p, a, b = R()
        g[p - 1] += [(i, a, b)]  # Build adjacency list with parent, a, b values
    r = [0] * (n)
    Pb = [0] * n  # Prefix sum array for 'b' values
    stk = [(0, 0, 0, 0)]  # Stack for DFS: (current_node, sum_a, sum_b, depth)
    
    while stk:
        u, pa, ub, dep = stk.pop()  # Pop from stack
        Pb[dep] = 0 if dep == 0 else Pb[dep - 1] + ub  # Compute prefix sum of b values
        # Find the maximum prefix length where sum of b values <= sum of a values
        r[u] = dep if Pb[dep] <= pa else br(Pb, pa, hi=dep) - 1
        for v, a, b in g[u]:  # Traverse children
            stk += [(v, pa + a, b, dep + 1)]  # Push child to stack with updated sums
    
    print(*r[1:])  # Print results excluding root (index 0)


# https://github.com/VaHiX/CodeForces/