# Problem: CF 2114 E - Kirei Attacks the Estate
# https://codeforces.com/contest/2114/problem/E

"""
E. Kirei Attacks the Estate

Purpose:
This code computes the threat value for each vertex in a tree, where the threat is defined as the maximum alternating sum along any vertical path starting from that vertex to the root.

Algorithm:
- The tree is processed in a bottom-up manner using BFS traversal.
- For each node, we track two values:
    - The maximum alternating sum ending at this node (as a "maximize" value).
    - The maximum alternating sum that can be extended from previous nodes while maintaining parity.
- The recurrence relation uses dynamic information to compute the maximum alternating sum for each node efficiently.

Time Complexity: O(n), where n is the number of vertices, since we process each vertex and edge once.
Space Complexity: O(n), due to storage for adjacency list, arrays to store intermediate values.

Techniques:
- Tree BFS traversal with parent tracking
- Dynamic programming on trees
- Post-order processing (bottom-up)
"""

import sys

input = lambda: sys.stdin.readline().rstrip()
for _ in range(int(input())):
    n = int(input())
    w = [0] + list(map(int, input().split())) + [0]  # dangers array with padding
    d = [[] for _ in range(n + 1)]
    for _ in range(n - 1):
        a, b = map(int, input().split())
        d[a].append(b)
        d[b].append(a)
    q = [1]  # BFS queue starting from root
    g = [-1] * (n + 2)  # parent tracking array
    x = [0] * (n + 2)   # threat values for each node
    while q:
        a = q.pop()
        b = g[a]        # parent of current node
        c = g[b]        # grandparent of current node
        # Compute threat value: current danger plus maximum benefit from grandparent path
        x[a] = w[a] + max(0, x[c] - w[b])
        for i in d[a]:  # traverse neighbors
            if i != g[a]:  # avoid going back to parent
                q.append(i)
                g[i] = a   # set current node as parent of neighbor
    print(" ".join(map(str, x[1:-1])))  # output results, excluding padding elements


# https://github.com/VaHiX/codeForces/