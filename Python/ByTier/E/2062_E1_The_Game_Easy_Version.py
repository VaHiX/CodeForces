# Problem: CF 2062 E1 - The Game (Easy Version)
# https://codeforces.com/contest/2062/problem/E1

"""
E1. The Game (Easy Version)
Algorithms/Techniques: Tree traversal, Lowest Common Ancestor (LCA), Binary lifting, Greedy
Time Complexity: O(n log n) per test case
Space Complexity: O(n) per test case

This solution implements a strategy for Cirno to choose a winning first move in the game on a tree.
The key idea is to determine whether Cirno can win by finding a node that allows her to place a subtree such that Daiyousei cannot make a valid move,
or at least ensures a winning sequence based on optimal play.

It uses binary lifting for efficient LCA computation and greedy selection of nodes.
"""

import sys

le = sys.__stdin__.read().split("\n")[::-1]  # Read all input and reverse it
af = []
for zo in range(int(le.pop())):  # Loop through each test case
    n = int(le.pop())  # Number of nodes
    l = list(map(int, le.pop().split()))  # Values of nodes
    Depth = [0] * n  # Depth of each node from root
    pi = [0]  # Stack to process DFS
    ar = [[] for _ in range(n)]  # Adjacency list representation of tree
    for _ in range(n - 1):  # Build adjacency list
        a, b = map(int, le.pop().split())
        a -= 1
        b -= 1
        ar[a].append(b)
        ar[b].append(a)
    
    jump = [0] * n  # Binary lifting table for LCA
    parent = [0] * n  # Parent of each node in DFS traversal
    po = [[] for k in range(n)]  # List of indices grouped by node value (for greediness)
    for k, v in enumerate(l):
        po[v - 1].append(k)  # Grouping nodes by their values
    
    ma = max(l) - 1  # Maximum node value minus 1
    
    # DFS traversal to build jump and parent tables
    while pi:
        u = pi.pop()
        ju = jump[u]
        du = Depth[u]
        if ju == 0:
            fju = u
        elif 2 * Depth[ju] - du == Depth[jump[ju]]:
            fju = jump[ju]
        else:
            fju = u
        for v in ar[u]:
            if parent[u] != v:  # Avoid going back to parent
                parent[v] = u
                pi.append(v)
                Depth[v] = du + 1
                jump[v] = fju

    la = ma  # Current max value being processed
    bo = False  # Flag to indicate if solution found
    
    # Iterate from highest node value down to lowest
    for k in range(la - 1, -1, -1):
        if po[k]:  # If nodes with this value exist
            te = None
            nte = None
            for u in po[k]:
                if te is None:
                    te = u
                else:
                    nu = u
                    mte = te
                    if Depth[te] > Depth[u]:
                        nu, te = te, nu  # Ensure te has lower depth to simplify traversal
                    while Depth[nu] > Depth[te]:
                        # Jump up using binary lifting or simple parent
                        nu = jump[nu] if Depth[jump[nu]] >= Depth[te] else parent[nu]
                    if te != nu:
                        # Found conflict; update best node so far and break
                        te, nte = mte, u
                        break
                    else:
                        # Update current best node to larger depth, if applicable
                        if Depth[u] > Depth[te]:
                            te = u
                        else:
                            te = mte

            for v in po[la]:  # For all nodes with the previous value
                if Depth[v] < Depth[te]:
                    af.append(te + 1)  # Valid choice found; add it to result
                    bo = True
                    break
                while Depth[v] > Depth[te]:
                    # Move up using binary lifting
                    v = jump[v] if Depth[jump[v]] >= Depth[te] else parent[v]
                if v != te:
                    af.append(te + 1)
                    bo = True
                    break
                if nte is not None:  # If there was a conflict in earlier part of loop
                    af.append(nte + 1)
                    bo = True
                    break
            la = k  # Move to next lower value group
            if bo:
                break  # Solution found — exit early
    
    if not (bo):  # No valid starting node found; Cirno loses
        af.append(0)

print("\n".join(map(str, af)))



# https://github.com/VaHiX/codeForces/