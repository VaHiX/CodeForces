# Problem: CF 2031 B - Penchick and Satay Sticks
# https://codeforces.com/contest/2031/problem/B

"""
B. Penchick and Satay Sticks

Purpose:
This code determines whether a given permutation of satay sticks can be sorted 
into increasing order [1, 2, ..., n] using only adjacent swaps where the two 
swapped elements differ by exactly 1.

Algorithm/Techniques:
- For each element in the permutation, check if it can "move" to its correct position (i) based on allowed operations.
- An element at index i can only move to positions i-1, i, or i+1 if the difference between elements is exactly 1.
- If an element p[i] is more than 2 positions away from i, it's impossible to reach its target position using valid moves.

Time Complexity: O(n) per test case
Space Complexity: O(1) excluding input storage

Input:
- First line contains number of test cases t
- For each test case:
  - First line contains n (number of elements)
  - Second line contains n integers forming a permutation

Output:
- "YES" if permutation can be sorted using allowed operations, otherwise "NO"
"""

import sys

inp = lambda func=int: list(map(func, sys.stdin.readline().split()))
t = inp()[0]
for _ in range(t):
    n = inp()[0]
    p = inp()
    for i in range(n):
        # If element p[i] is more than 2 positions away from its target position i,
        # it's impossible to bring it there using allowed swaps
        if p[i] - i > 2 or p[i] < i:
            print("NO")
            break
    else:
        print("YES")


# https://github.com/VaHiX/codeForces/