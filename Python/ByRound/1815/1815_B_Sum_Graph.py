# Problem: CF 1815 B - Sum Graph
# https://codeforces.com/contest/1815/problem/B

"""
Interactive problem to determine a hidden permutation p of length n.
The approach uses the following algorithm:
1. For each query of type 1 (x), we add edges between nodes i and x-i for valid i.
2. Query distances between pairs of nodes in the permutation to infer structure.
3. Build two candidate permutations based on the graph structure.

This is based on observing that by querying x = n+1 and x = n, we form a structure where distances
reveal information about the order of elements in the permutation.
We construct two possible permutations based on the distances from a node with maximum distance.

Time Complexity: O(n^2) - due to querying distances between pairs of nodes, and constructing permutations.
Space Complexity: O(n) - to store permutations and distance information.
"""

import sys

input = sys.stdin.readline


def tp1(x):
    print("+", x, flush=True)
    return int(input())


def tp2(i, j):
    print("?", i, j, flush=True)
    return int(input())


def sol():
    n = int(input())
    # Create lists for building permutations
    sm = [i + 1 for i in range(n // 2)][::-1]  # [n//2, n//2-1, ..., 1]
    bg = [n - i for i in range((n + 1) // 2)][::-1]  # [n, n-1, ..., (n+1)//2]
    
    # Build first candidate permutation alternately from sm and bg
    prob1 = []
    for i in range(n):
        if i % 2 == 0:
            prob1.append(bg.pop())  # Take from bg list
        else:
            prob1.append(sm.pop())  # Take from sm list
    
    # Second permutation is reverse of first
    prob2 = prob1[::-1]
    
    # Perform type 1 queries to build graph structure
    tp1(n + 1)  # Query with x = n+1
    tp1(n)      # Query with x = n
    
    # Get distances from node 1 to all other nodes
    dist = [0]
    for i in range(2, n + 1):
        dist.append(tp2(1, i))

    # Find node with maximum distance from node 1
    mx = max(dist)
    mxid = dist.index(mx) + 1  # Index of node with max distance
    
    # Prepare final answers based on distances from max node
    ans1 = []
    ans2 = []
    for i in range(1, n + 1):
        if i == mxid:
            # If current node is the max distant node, use first element of permutations
            ans1.append(prob1[0])
            ans2.append(prob2[0])
        else:
            # Query the distance to current node from the max node
            tmp = tp2(mxid, i)
            # Assign corresponding values from the two permutations
            ans1.append(prob1[tmp])
            ans2.append(prob2[tmp])

    print("!", *ans1, *ans2, flush=True)

    # Re-read n to continue with next test case
    n = int(input())
    return


T = int(input())
for i in range(T):
    sol()


# https://github.com/VaHiX/CodeForces/