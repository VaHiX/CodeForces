# Problem: CF 2078 B - Vicious Labyrinth
# https://codeforces.com/contest/2078/problem/B

"""
B. Vicious Labyrinth

Purpose:
This code solves a problem where we have n cells in a labyrinth, each with a person initially located at position i (where cell n is the exit). 
We are allowed to place teleporters such that each person uses exactly k teleportations. Each teleporter moves a person from cell i to another cell a_i.
Goal: Minimize the total distance of all individuals from the exit after k teleportations.

Algorithm/Techniques:
- Based on parity of k, we determine how to distribute the teleporter destinations.
- For odd k: we can create a nearly symmetric configuration that minimizes distance sums.
- For even k: we adjust the pattern slightly to maintain minimum sum but satisfy constraints.

Time Complexity: O(n) per test case
Space Complexity: O(n) for storing result array
"""

import sys

input = sys.stdin.readline
for i in range(int(input())):
    n, k = map(int, input().split())
    if k % 2:  # If k is odd
        # For odd k, use pattern [n, n, ..., n, n-1] 
        # This ensures minimum sum of distances after k operations
        print(*[n] * (n - 1) + [n - 1])
    else:  # If k is even
        # For even k, use pattern [n-1, n-1, ..., n, n-1]
        # This pattern ensures valid configuration with minimal sum of distances
        print(*[n - 1] * (n - 2) + [n, n - 1])


# https://github.com/VaHiX/codeForces/