# Problem: CF 1833 G - Ksyusha and Chinchilla
# https://codeforces.com/contest/1833/problem/G

"""
Algorithm: Tree edge cutting to form branches
Approach:
- This problem involves decomposing a tree into branches (3-vertex trees) by cutting edges.
- The idea is to use DFS traversal to determine which edges need to be cut.
- For each vertex, track whether it needs 1 or 2 connections to form a complete branch.
- A vertex must be in exactly one branch.
- Use a stack-based DFS to process the tree and decide on edges to cut.

Time Complexity: O(n) per test case
Space Complexity: O(n) for graph storage and auxiliary arrays
"""

import sys

input = sys.stdin.readline


def solve():
    n = int(input())
    G = [[] for _ in range(n)]
    for i in range(n - 1):
        u, v = [int(x) - 1 for x in input().split()]
        G[u].append((v, i))
        G[v].append((u, i))

    cut = [False] * n  # Tracks which edges are cut
    need1 = [False] * n  # Indicates if vertex needs 1 more connection
    need2 = [False] * n  # Indicates if vertex needs 2 more connections
    par = [-1] * n  # Parent of each vertex in DFS tree
    stack = [(~0, n - 1), (0, n - 1)]  # Stack for DFS, storing (vertex, parent_edge_index)
    
    while stack:
        u, epar = stack.pop()
        if u >= 0:
            # Process children
            for v, echild in G[u]:
                if v == par[u]:
                    continue
                par[v] = u
                stack.append((~v, echild))  # Mark for post-processing
                stack.append((v, echild))   # Mark for pre-processing
        else:
            # Process vertex in post-order (after children are processed)
            u = ~u

            for v, echild in G[u]:
                if cut[echild]:
                    continue

                # If parent edge is marked as cut and child needs either type
                if (cut[epar] and (need1[v] or need2[v])) or (need1[u] and need1[v]):
                    out.append(-1)
                    return

                # If child needs 1 connection, then cut current edge
                if need1[v]:
                    cut[epar] = True

                # If child needs 2 connections and current vertex needs 1, cut edge
                elif need2[v]:
                    if need1[u]:
                        cut[epar] = True
                    else:
                        need1[u] = True

            # If parent edge isn't cut and there's no need1 on current vertex
            if not cut[epar] and not need1[u]:
                need2[u] = True

    if not cut[n - 1]:
        out.append(-1)
        return

    cut.pop()  # Remove last element since it's not a real edge index
    res = [i + 1 for i, c in enumerate(cut) if c]
    out.append(len(res))
    out.append(" ".join(map(str, res)))
    return


T = int(input())
out = []
for _ in range(T):
    solve()
print("\n".join(map(str, out)))


# https://github.com/VaHiX/CodeForces/