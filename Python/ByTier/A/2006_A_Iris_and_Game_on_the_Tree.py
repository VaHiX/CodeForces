# Problem: CF 2006 A - Iris and Game on the Tree
# https://codeforces.com/contest/2006/problem/A

"""
Problem: Iris and Game on the Tree

Purpose:
This code solves a game theory problem on a tree where each node has a value (0, 1, or ?).
The goal is to compute the final score of the tree under optimal play by two players:
- Iris (maximizes score)
- Dora (minimizes score)

Each leaf's weight is defined as the difference between count of "10" and "01" substrings
of the path from root to that leaf. The score is the number of leaves with non-zero weight.

Algorithms/Techniques:
- Tree traversal and degree calculation
- Game theory (minimax) on trees
- Greedy logic for optimal play based on node types

Time Complexity: O(n) per test case, where n is the number of nodes.
Space Complexity: O(n) for storing tree structure and auxiliary arrays.

"""

def solve():
    n = int(input())
    deg = [0] * n  # Degree of each node
    for i in range(n - 1):
        x, y = map(int, input().split())
        deg[x - 1] += 1  # Adjusting for 0-based indexing
        deg[y - 1] += 1
    
    c0 = c1 = c = 0  # Counters for leaves with "0", "1", and "?" values respectively
    s = input()  # String representing node values
    
    # Loop through all nodes except root (node 0)
    for i in range(1, n):
        if deg[i] == 1:  # Check if the node is a leaf (degree = 1)
            if s[i] == "0":
                c0 += 1
            elif s[i] == "1":
                c1 += 1
            else:
                c += 1  # "?" case

    # Based on root's value, determine the return based on game theory logic
    if s[0] == "0":
        # Iris wants to maximize score; if root is 0, minimize loss in 1s
        return c1 + (c + 1) // 2
    elif s[0] == "1":
        # If root is 1, minimize loss in 0s
        return c0 + (c + 1) // 2
    elif c0 != c1:
        # If counts differ, pick the side that gives more advantage
        return max(c0, c1) + c // 2
    else:
        # Both sides are equal; calculate extra based on parity of question marks and internal nodes
        c2 = 0
        for i in range(1, n):
            if deg[i] != 1 and s[i] == "?":  # Count non-leaf "?" nodes
                c2 ^= 1  # XOR to simulate parity effect of optimal play
        return c0 + (c + c2) // 2


import sys

input = lambda: sys.stdin.readline().rstrip()
t = int(input())
for i in range(t):
    print(solve())


# https://github.com/VaHiX/codeForces/