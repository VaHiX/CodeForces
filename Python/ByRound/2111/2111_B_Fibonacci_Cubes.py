# Problem: CF 2111 B - Fibonacci Cubes
# https://codeforces.com/contest/2111/problem/B

"""
B. Fibonacci Cubes

Purpose:
This program determines whether a set of n Fibonacci-sized cubes can fit into m rectangular boxes,
given the constraints that cubes must be stacked such that their sides are parallel to the box sides,
and no larger cube can be placed on top of a smaller one.

Algorithms/Techniques:
- Precomputed Fibonacci numbers
- Greedy stacking strategy based on sorted dimensions
- Dimensional comparison to check if all cubes fit within a box

Time Complexity: O(n * m) where n is the number of cubes and m is the number of boxes.
Space Complexity: O(n + m) for storing Fibonacci numbers and box dimensions.

Input Format:
- First line: number of test cases t
- For each test case:
  - Line 1: n (number of cubes), m (number of boxes)
  - Next m lines: w, l, h (dimensions of each box)

Output Format:
- For each test case, a string of length m where '1' indicates the box can fit all cubes, '0' otherwise.
"""

import sys

input = sys.stdin.readline
f = [1, 2, 3, 5, 8, 13, 21, 34, 55, 89]  # Precomputed Fibonacci numbers up to f[10]

for i in range(int(input())):  # Process each test case
    n, m = map(int, input().split())  # Read number of cubes and boxes
    out = []  # Store results for current test case
    
    for j in range(m):  # Process each box
        w, l, h = map(int, input().split())  # Read dimensions of the box
        
        # Check if the largest cube (f[n-1]) can fit in the smallest dimension of the box
        # and the second-largest cube (f[n-2]) can fit in at least one dimension
        if max(w, l, h) >= f[n - 1] + f[n - 2] and min(w, l, h) >= f[n - 1]:
            out.append("1")  # Cube fits
        else:
            out.append("0")  # Cube doesn't fit
    
    print("".join(out))  # Output results for current test case


# https://github.com/VaHiX/codeForces/