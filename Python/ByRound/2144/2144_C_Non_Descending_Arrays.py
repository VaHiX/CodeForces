# Problem: CF 2144 C - Non-Descending Arrays
# https://codeforces.com/contest/2144/problem/C

"""
C. Non-Descending Arrays
Algorithm: Greedy + Bitmasking / Dynamic Programming
Time Complexity: O(n^2) per test case
Space Complexity: O(1) excluding input storage

Approach:
- For each pair of elements at index i, decide whether to swap them or not,
  based on maintaining non-decreasing order in both arrays.
- We process elements from left to right and determine valid swaps.
- The number of such valid "groups" (where swapping can occur without breaking
  the sorted property) determines how many independent binary choices we have.
- Since each group has two options (swap or not), answer is 2^(number_of_groups).
"""

import sys

tc = int(sys.stdin.readline())
for _ in range(tc):
    n = int(sys.stdin.readline())
    a = list(map(int, sys.stdin.readline().split()))
    b = list(map(int, sys.stdin.readline().split()))
    u = 1  # Start with 1 group
    for i in range(n - 1):
        # If current order breaks non-descending property, swap elements
        if a[i] > a[i + 1] or b[i] > b[i + 1]:
            a[i], b[i] = b[i], a[i]
        # Check compatibility: after swapping, check if we can still maintain sorted order in next step
        if a[i] <= b[i + 1] and b[i] <= a[i + 1]:
            u += 1  # Increment group count if both conditions meet
    print((2**u) % 998244353)


# https://github.com/VaHiX/codeForces/