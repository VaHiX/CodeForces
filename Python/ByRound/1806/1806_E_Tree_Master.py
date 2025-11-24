# Problem: CF 1806 E - Tree Master
# https://codeforces.com/contest/1806/problem/E

"""
Tree Master Problem Solution
Algorithms: Tree traversal, memoization, path compression
Time Complexity: O(n + q * log n) where n is number of nodes and q is number of queries
Space Complexity: O(n) for storing tree structure, depth, and DP arrays

The solution preprocesses the tree to compute prefix sums for each node's path to root,
then uses memoization to efficiently answer queries by traversing up the tree.
"""

import collections
import sys

input = sys.stdin.readline


n, q = map(int, input().split())
a = list(map(int, input().split()))
p = [-1] + list(map(lambda x: int(x) - 1, input().split()))  # Convert to 0-indexed
queries = []
for _ in range(q):
    queries.append(list(map(int, input().split())))

# Build adjacency list representation of the tree
g = [[] for _ in range(n)]
for i, j in enumerate(p[1:], 1):
    g[j].append(i)

# dp[i] stores the sum of a[ancestor]^2 for all ancestors of node i (including itself)
dp = [0] * n
dp[0] = a[0] ** 2  # Root node
depth = [0] * n  # Depth of each node

# BFS to compute depth and dp values
stack = collections.deque(g[0])
while stack:
    i = stack.popleft()  # Current node
    j = p[i]  # Parent of current node
    depth[i] = depth[j] + 1  # Depth is parent's depth + 1
    dp[i] = a[i] ** 2 + dp[j]  # Square of current node's weight plus parent's dp value
    for k in g[i]:
        stack.append(k)  # Add children to queue for processing


dic = collections.defaultdict(int)  # Memoization cache for query results


def f(u, v):
    # Ensure u is the smaller index (for consistent key in cache)
    if u > v:
        u, v = v, u
    if (u, v) in dic:
        return dic[(u, v)]

    u_tmp, v_tmp = u, v  # Temporary variables to traverse up the tree
    res = 0  # Accumulated result for this query

    # Traverse up while depths are not equal, but with a bit optimization 
    while u_tmp != v_tmp and depth[u_tmp] & ((1 << 7) - 1):
        res += a[u_tmp] * a[v_tmp]  # Multiply weights at current levels
        u_tmp, v_tmp = p[u_tmp], p[v_tmp]  # Move up one level in tree

    # If the nodes have reached the same point, return partial result + dp value
    if u_tmp == v_tmp:
        dic[(u, v)] = res + dp[u_tmp]
        return dic[(u, v)]
    # Otherwise, recursively go one level up and continue the process
    else:
        dic[(u, v)] = res + f(p[u_tmp], p[v_tmp]) + a[u_tmp] * a[v_tmp]
        return dic[(u, v)]


# Process all queries
for i, j in queries:
    print(f(i - 1, j - 1))  # Convert to 0-indexed


# https://github.com/VaHiX/CodeForces/