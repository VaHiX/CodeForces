# Problem: CF 1806 D - DSU Master
# https://codeforces.com/contest/1806/problem/D

"""
Purpose:
This code calculates the sum of values of all permutations of length k for each k from 1 to n-1,
where the value of a permutation is defined by a specific graph construction process using DSU
and directed edges based on array `a`.

Algorithms/Techniques:
- Dynamic Programming with recurrence relations
- Modular arithmetic for large numbers
- Efficient computation using precomputed states

Time Complexity: O(n)
Space Complexity: O(1)

The algorithm maintains three variables (p, q, r) that represent states in a recurrence relation
to compute the result for each k efficiently without generating all permutations explicitly.
"""

M = 998244353
for a in [*open(0)][2::2]:  # Read input lines skipping first two lines
    p, q, r = 0, 1, 1  # Initialize state variables
    for x in map(int, a.split()):  # Process each element of the array `a`
        # Update state variables using recurrence relation
        # This represents the core DP transition for calculating contribution of each step
        p, q, r = (r * p + q - q * x) % M, (r - x) * q % M, r + 1
        print(p)  # Output the sum of values for current k


# https://github.com/VaHiX/CodeForces/