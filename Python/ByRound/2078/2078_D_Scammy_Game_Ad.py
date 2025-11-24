# Problem: CF 2078 D - Scammy Game Ad
# https://codeforces.com/contest/2078/problem/D

"""
D. Scammy Game Ad
Purpose:
    This code solves a game problem where pairs of gates (left and right) perform operations on lane counts.
    Each gate either adds a constant or multiplies the current count by a factor (minus 1 for multiplication gain).
    The goal is to maximize the total number of people across both lanes after processing all pairs.

Algorithms/Techniques:
    - Greedy backward simulation
    - Dynamic tracking of left and right lane populations

Time Complexity: O(n) per test case, where n is the number of gate pairs.
Space Complexity: O(n) for storing the input data.

Input Format:
    - First line: number of test cases t
    - For each test case:
        + First line: number of pairs n
        + Next n lines: left gate info followed by right gate info

Output Format:
    - For each test case: maximum total people in both lanes at end
"""

import sys

input = sys.stdin.readline
for _ in range(int(input())):
    n = int(input())
    a = []
    for _ in range(n):
        b, c, d, e = input().split()
        a.append((b, int(c), d, int(e)))
    l, r, k = 1, 1, 0
    # Process gates from last to first (backwards)
    for b, c, d, e in a[::-1]:
        m = max(l, r)  # Current maximum of left and right lane populations
        if b == "x":
            # Multiplication operation on left gate: gain (c - 1) * m people
            l += (c - 1) * m
        else:
            # Addition operation on left gate: gain c people
            k += c * m  # Add to total allocation buffer for later use
        if d == "x":
            # Multiplication operation on right gate: gain (e - 1) * m people
            r += (e - 1) * m
        else:
            # Addition operation on right gate: gain e people
            k += e * m  # Add to total allocation buffer for later use
    print(k + l + r)


# https://github.com/VaHiX/codeForces/