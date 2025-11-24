# Problem: CF 1843 F1 - Omsk Metro (simple version)
# https://codeforces.com/contest/1843/problem/F1

"""
Algorithm: Tree Path Sum Query with Range Min/Max
Techniques: 
- Path sum queries on tree using prefix sums and range min/max tracking
- Dynamic tree construction with path compression

Time Complexity: O(n) for each test case, where n is the number of events
Space Complexity: O(n) for storing tree structure and prefix sums

This code handles queries for adding new nodes to a tree and checking 
if there exists a subpath between node 1 and another node with a sum of weights equal to k.
The key insight is to track the minimum and maximum possible prefix sums along paths
from root (node 1) to each node, allowing efficient range checking for subpath sums.
"""

from sys import stdin

input = lambda: stdin.readline().rstrip("\r\n")


for _ in range(int(input())):
    n = int(input())
    par = [0] * (n + 5)
    mn = [0] * (n + 5)
    mx = [0] * (n + 5)

    mnNode = [0] * (n + 5)
    mxNode = [0] * (n + 5)
    u = 1

    mx[1] = mxNode[1] = 1

    for i in range(n):
        q = input().split()

        if q[0] == "+":
            u += 1
            p = int(q[1])
            x = int(q[2])

            # Update the min and max prefix sums for the new node
            mnNode[u] = min(mnNode[u], mnNode[p] + x)
            mxNode[u] = max(mxNode[u], mxNode[p] + x)
            # Propagate the min and max values up the tree
            mn[u] = min(mn[p], mnNode[u])
            mx[u] = max(mx[p], mxNode[u])

        else:
            # Process query for path from node 1 to node v with target sum x
            v = int(q[2])
            x = int(q[3])
            # Check if target sum x is within range [mn[v], mx[v]]
            print("YES" if mn[v] <= x <= mx[v] else "NO")


# https://github.com/VaHiX/CodeForces/