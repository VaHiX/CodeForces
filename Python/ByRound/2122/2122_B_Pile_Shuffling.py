# Problem: CF 2122 B - Pile Shuffling
# https://codeforces.com/contest/2122/problem/B

"""
B. Pile Shuffling
Algorithms/Techniques: Greedy, Simulation

Time Complexity: O(n) where n is the number of piles (sum of n over all test cases is bounded by 2*10^5)
Space Complexity: O(1)

The problem requires minimizing the number of operations to transform piles from an initial state to a target state.
Each pile has a top portion of zeros and a bottom portion of ones. We are allowed to move elements between piles.

Key insight:
For each pile, we compute how many operations are needed based on:
- Excess zeros that must be moved out (max(0, a - c))
- Excess ones that must be moved out (max(0, b - d))
- Additional operations due to the structure of target (b > d) * min(a, c)

This greedy approach calculates the total "deficit" and "excess" for each pile's top and bottom sections,
and accounts for necessary reorganization.
"""

import sys

I = sys.stdin.readline
for _ in range(int(I())):
    s = 0
    for _ in range(int(I())):
        a, b, c, d = map(int, I().split())  # Read current top zeros (a), bottom ones (b), target top zeros (c), target bottom ones (d)
        s += max(0, a - c) + max(0, b - d) + (b > d) * min(a, c)  # Accumulate required operations
    print(s)


# https://github.com/VaHiX/codeForces/