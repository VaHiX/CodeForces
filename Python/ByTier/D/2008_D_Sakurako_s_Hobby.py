# Problem: CF 2008 D - Sakurako's Hobby
# https://codeforces.com/contest/2008/problem/D

"""
D. Sakurako's Hobby

Purpose:
This code computes for each element in a permutation, the count of "black" (represented by '0') elements 
that are reachable through a cycle formed by the permutation p. Each index i points to p[i], forming cycles,
and we want to know how many black elements exist in each cycle.

Algorithm:
- Process each element of the permutation once.
- For each unvisited element, traverse the cycle until we return to the start.
- During traversal, compute the count of black nodes in the cycle.
- Assign this count to all nodes in the cycle.
- Uses Union-Find like logic with visited tracking and a "size" counter to avoid redundant computations.

Time Complexity: O(n) for each test case
Space Complexity: O(n) for arrays us, b, p

Input Format:
- First line: number of test cases t
- For each test case:
  - Line 1: n (number of elements)
  - Line 2: permutation p of length n
  - Line 3: string s of length n with '0' or '1'

Output:
- For each test case, print n integers F(1), F(2), ..., F(n) where F(i) is the number of black elements reachable from i.
"""

t = int(input())
for _ in range(t):
    n = int(input())
    b = [0] * (n + 1)      # Stores result for each index
    us = [0] * (n + 1)     # Visited array: 0 = unvisited, 1 = being processed, 2 = done
    p = [k - 1 for k in map(int, input().split())]  # Convert to 0-indexed permutation
    s = input()            # String representing color ('0' = black)
    
    for i in range(0, n):
        if us[i]:          # Skip if already processed
            continue
        sz = 0             # Count of '0's (black nodes) in this cycle
        start = i          # Keep track of where we started to come back later
        
        # First pass: compute the size of the cycle and count of black nodes
        while not us[i]:
            us[i] = 1      # Mark as being processed
            sz += s[i] == "0"  # Increment if current node is black
            i = p[i]       # Move to next node in permutation
        
        # Second pass: assign the computed count back to all nodes in the cycle
        i = start          # Start from beginning of the cycle again
        while us[i] != 2:  # Continue until we've assigned values to all nodes in cycle
            b[i] = sz      # Assign count of black nodes in this cycle to current node
            us[i] = 2      # Mark as fully processed
            i = p[i]       # Move to next node

    print(" ".join(map(str, b[:-1])))  # Output result excluding dummy index at end


# https://github.com/VaHiX/codeForces/