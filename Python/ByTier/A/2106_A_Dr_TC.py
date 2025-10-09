# Problem: CF 2106 A - Dr. TC
# https://codeforces.com/contest/2106/problem/A

# flowerbox
"""
Purpose: This code solves a problem where Dr. TC creates a grid of binary strings 
         by flipping each character of an input string in turn. The goal is to 
         count the total number of '1's in the resulting grid.

Algorithms/Techniques:
- String manipulation and counting
- Mathematical pattern recognition

Time Complexity: O(n) per test case, where n is the length of the binary string s.
Space Complexity: O(1) excluding input storage, as we only use a constant amount of extra space.

Input Format:
- First line: number of test cases t
- For each test case:
  - First line: integer n (length of string)
  - Second line: binary string s of length n

Output Format:
- For each test case: integer representing total count of '1's in the grid
"""

# Read all lines from stdin, skip first line, take every second line starting from index 2
for s in [*open(0)][2::2]:
    # Count occurrences of '1' and '0' in the string s
    a, b = map(s.count, "10")  # a = count of '1's, b = count of '0's
    
    # Compute total number of 1s in the grid:
    # - Each row has one '1' less than the original string (due to flip)
    # - There are n rows
    # - Each row contributes (len(s) - 1) 1s from the flipped position, 
    #   plus the rest come from unflipped positions
    print(a * (len(s) - 2) + b)


# https://github.com/VaHiX/codeForces/