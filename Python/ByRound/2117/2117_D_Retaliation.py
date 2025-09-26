# Problem: CF 2117 D - Retaliation
# https://codeforces.com/contest/2117/problem/D

"""
D. Retaliation
Purpose:
    Determine if an array can be reduced to all zeros using two types of operations:
        1. Subtract from each element `i` (0-indexed). 
        2. Subtract from each element `n - i` (0-indexed).
    
    Each operation reduces all elements in a specific pattern.
    The main idea is to model the array as a linear function and verify if all
    elements can reach zero through such operations.

Algorithms/Techniques:
    - Linear algebra / slope analysis
    - Arithmetic progression modeling
    - Modular arithmetic for validation

Time Complexity: O(n) per test case
Space Complexity: O(1)

"""

import sys

input = sys.stdin.readline
for i in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    
    # Compute parameters x and y that define the linear function:
    # a[i] = x * (i + 1) + y * (n - i)
    # We use the first and last elements to fit a line
    x = (n * a[-1] - a[0]) // (n * n - 1)
    y = a[-1] - x * n
    
    # Check if the division is exact and both x, y are non-negative
    if (n * a[-1] - a[0]) % (n * n - 1) == 0 and min(x, y) >= 0:
        f = 1  # Flag to indicate if all elements match the pattern
        for j in range(n):
            # Check if current element fits the linear model
            f &= int(a[j] == x * (j + 1) + y * (n - j))
        print("YES" if f else "NO")
    else:
        print("NO")


# https://github.com/VaHiX/codeForces/