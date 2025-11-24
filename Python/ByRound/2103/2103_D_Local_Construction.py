# Problem: CF 2103 D - Local Construction
# https://codeforces.com/contest/2103/problem/D

"""
D. Local Construction

Problem Description:
Given an array 'a' where a[i] represents the iteration number when element p[i] is removed from a permutation p of size n, 
construct any valid permutation p that satisfies this array. 

Approach:
- The process alternates between removing local minima (odd iterations) and local maxima (even iterations).
- Each element contributes to the answer by placing it in an order that ensures correct removal iteration.
- We build a tree structure where each node is a layer of removals, and we assign values based on the removal order.

Time Complexity: O(n log n)
Space Complexity: O(n)

This solution uses a depth-first-like approach:
1. For each element, determine which "layer" (depth) it belongs to.
2. Assign numbers to elements such that their removal happens at the correct time,
   by placing smaller values earlier for odd layers and larger later for even layers.

Key technique:
Tree traversal with layered assignment
"""

import sys

input = lambda: sys.stdin.readline().rstrip()
for _ in range(int(input())):
    n = int(input())
    w = list(map(int, input().split()))
    x = max(w) + 1
    d = [[] for _ in range(n)]
    for i in range(n):
        if w[i] == -1:
            a = i  # Index of the last remaining element
        else:
            d[w[i] - 1].append(i)
    
    l, r, ew = 1, n, [0] * n  # l: left pointer, r: right pointer, ew: result array
    
    for i in range(n):
        for j in d[i]:  # Traverse nodes at depth i
            if j < a:
                if i % 2:  # Odd depths: assign smaller values first
                    ew[j] = l
                    l += 1
                else:  # Even depths: assign larger values first
                    ew[j] = r
                    r -= 1
            else:
                break
        for j in d[i][::-1]:  # Reverse traversal for second pass
            if j > a:
                if i % 2:
                    ew[j] = l
                    l += 1
                else:
                    ew[j] = r
                    r -= 1
    
    ew[a] = l  # Assign the final remaining element
    print(" ".join(map(str, ew)))


# https://github.com/VaHiX/codeForces/