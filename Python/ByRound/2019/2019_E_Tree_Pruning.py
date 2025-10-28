# Problem: CF 2019 E - Tree Pruning
# https://codeforces.com/contest/2019/problem/E

"""
E. Tree Pruning
Algorithm: BFS + Greedy
Purpose: Given a rooted tree, find the minimum number of operations to remove leaves so that all remaining leaves are at the same distance from the root.

The approach uses BFS traversal of the tree, keeping track of how many "extra" leaves we have (i.e., leaves that need to be removed) at each level. 
At every node, we greedily try to minimize the number of operations by removing nodes that would not contribute to making all leaves at the same distance.

Time Complexity: O(n) per test case
Space Complexity: O(n) for storing adjacency list and auxiliary arrays
"""

import sys

input = sys.stdin.buffer.readline
for _ in range(int(input())):
    n = int(input())
    adj = [[] for _ in range(n)]
    for _ in range(n - 1):
        u, v = [int(x) - 1 for x in input().split()]
        adj[u].append(v)
        adj[v].append(u)
    
    # Calculate degrees for each node; subtract 1 if not root (since root has no parent edge)
    deg = [len(adj[v]) - int(v != 0) for v in range(n)]
    pre = [-1] * n
    ans = n - 1
    add = 0
    Q = [0]
    
    while Q:
        nQ = []
        for v in Q:
            # If current node is a leaf (not root) and has degree 1
            if len(adj[v]) == 1 and v != 0:
                p = v
                add -= 1  # Reduce count of nodes we're trying to keep
                # Traverse up the tree towards root, removing extra leaves
                while pre[p] != 0 and deg[pre[p]] == 1:
                    add -= 1  # Reduce further since we are removing an unnecessary leaf
                    p = pre[p]
                deg[pre[p]] -= 1  # Update degree of parent node
            else:
                # Process children
                for u in adj[v]:
                    if u == pre[v]:  # Skip parent node to avoid going back
                        continue
                    add += 1  # Increase count of nodes we're considering
                    pre[u] = v  # Set parent of node u
                    nQ.append(u)  # Add child for next BFS level
        Q = nQ
        ans = min(ans, n - 1 - add)  # Update minimum operations needed
    
    print(ans)


# https://github.com/VaHiX/codeForces/