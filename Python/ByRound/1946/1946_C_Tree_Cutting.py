# Problem: CF 1946 C - Tree Cutting
# https://codeforces.com/contest/1946/problem/C

"""
Algorithm: Binary Search on Answer + DFS Tree Traversal
Approach:
- We binary search on the answer 'x' (minimum size of each component)
- For a given x, we check if it's possible to remove exactly k edges such that all remaining components have size >= x
- To check, we perform a post-order DFS traversal:
    - For each node, we calculate its subtree size
    - If the subtree size is >= x, we count it as a valid component (we can cut it off)
    - Otherwise, we merge it into its parent's subtree
- The result is the maximum x for which we can get more than k components (i.e., we can cut k edges)
Time Complexity: O(n * log(n)) where n is the number of nodes in the tree
Space Complexity: O(n) for storing the tree and auxiliary arrays
"""

import sys

input = sys.stdin.readline


def check(x):
    res = 0
    cnt = [1] * n  # Initialize each node's subtree size to 1
    for v in order[::-1]:  # Process nodes in reverse post-order
        if cnt[v] >= x:  # If this subtree is large enough to be a separate component
            res += 1
        elif par[v] >= 0:  # If this node has a parent (not root)
            cnt[par[v]] += cnt[v]  # Merge this subtree into parent's subtree
    return res > k  # Return true if number of components exceeds k


for _ in range(int(input())):
    n, k = map(int, input().split())
    g = [[] for i in range(n)]  # Adjacency list representation of the tree
    for i in range(n - 1):
        v, u = map(int, input().split())
        v -= 1  # Convert to 0-based indexing
        u -= 1
        g[v].append(u)
        g[u].append(v)
    
    par = [0] * n  # Parent array for DFS traversal
    par[0] = -1  # Root has no parent
    s = [0]  # Stack for DFS traversal starting from root (node 0)
    order = []  # Store post-order traversal
    while s:
        v = s.pop()
        order.append(v)
        for u in g[v]:
            if u != par[v]:  # Avoid going back to parent
                par[u] = v
                s.append(u)
    
    # Binary search on the answer
    l, r = 0, n + 1
    while l + 1 < r:
        mid = (l + r) // 2
        if check(mid):
            l = mid  # Try larger x
        else:
            r = mid  # Try smaller x
    print(l)


# https://github.com/VaHiX/CodeForces/