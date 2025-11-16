# Problem: CF 2007 D - Iris and Game on the Tree
# https://codeforces.com/contest/2007/problem/D

"""
D. Iris and Game on the Tree

Purpose:
This code solves a game played on a tree where each vertex has a value of '0', '1', or '?'.
The goal is to compute the final score (number of leaves with non-zero weight) when both players 
(play optimally) fill in unspecified values ('?').

The key insight is that for each leaf, the difference between # of "10" and # of "01" substrings
in the path from root to leaf determines its weight.
We determine how many leaves will have non-zero weights after both players choose optimally.

Techniques:
- Tree traversal to compute degrees of nodes.
- Greedy analysis based on terminal and non-terminal '?'
  values in paths from root to leaves.
- Game theory: max-min strategy for two players choosing '?' values.

Time Complexity: O(n)
Space Complexity: O(n)

"""
from sys import stdin

input = stdin.readline
t = int(input())
for _ in range(t):
    n = int(input())
    deg = [0] * (n + 1)  # degree array for the tree
    for i in range(n - 1):
        u, v = map(int, input().split())
        deg[u] += 1  # increment degree of vertex u
        deg[v] += 1  # increment degree of vertex v
    
    x, y, z, w = 0, 0, 0, 0  # counts for leaf nodes with degree=1
    s = " " + input()  # prepend space to make indexing start from 1
    
    # Process each node (except root) to classify leaves based on their value and degree
    for i in range(2, n + 1):  # Start from 2 since root (1) is never a leaf
        if deg[i] == 1:  # This is a leaf node
            if s[i] == "0":
                x += 1  # count of leaves with '0' and degree=1
            elif s[i] == "1":
                y += 1  # count of leaves with '1' and degree=1
            else:
                z += 1  # count of leaves with '?' and degree=1
        elif s[i] == "?":  # internal node marked as '?'
            w += 1  # count of '?', non-leaf nodes

    # Based on the root's value, calculate the score using game theory logic
    if s[1] == "0":
        print(y + (z + 1) // 2)
    elif s[1] == "1":
        print(x + (z + 1) // 2)
    else:
        # Root is '?', use max of x and y to get best outcome for Iris
        # then add effect of remaining '?' nodes using greedy strategy
        print(max(x, y) + (z + (w % 2 if x == y else 0)) // 2)


# https://github.com/VaHiX/codeForces/