# Problem: CF 1713 C - Build Permutation
# https://codeforces.com/contest/1713/problem/C

"""
C. Build Permutation

Purpose:
This code attempts to construct a permutation of integers [0, 1, ..., n-1] such that for each element at index i,
the sum of the element and its index (i + a[i]) is a perfect square. The algorithm uses a greedy approach 
to assign values by filling segments in reverse order, based on perfect squares.

Algorithms/Techniques:
- Greedy assignment with perfect square constraints
- Iteratively fills array in reverse using computed perfect squares

Time Complexity: O(n * sqrt(n)) - For each element, we compute next perfect square and fill a segment.
Space Complexity: O(n) - A single array of size n is used.
"""

import math
from sys import stdin

for _ in range(int(stdin.readline().strip())):
    n = int(stdin.readline().strip())
    a, t = [0] * n, n - 1  # Initialize array and set 't' to last index
    while True:
        ns = math.ceil(math.sqrt(t)) ** 2  # Compute next perfect square >= t
        for i in range(ns - t, t + 1):  # Fill elements from ns-t to t
            a[i] = ns - i  # Assign value based on difference from perfect square
        t = ns - t - 1  # Update t to new starting point
        if t < 0:  # Stop when t becomes negative
            break
    print(*a)


# https://github.com/VaHiX/codeForces/