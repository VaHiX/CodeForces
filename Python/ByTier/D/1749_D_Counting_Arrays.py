# Problem: CF 1749 D - Counting Arrays
# https://codeforces.com/contest/1749/problem/D

"""
Algorithm: Dynamic Programming with GCD and Modular Arithmetic
Purpose: Count the number of ambiguous arrays of length 1 to n with elements in range [1, m].
Time Complexity: O(n * log(n)) due to GCD computations and loop over n elements.
Space Complexity: O(1) as we only use a few variables for computation.

The solution uses inclusion-exclusion principle to calculate how many arrays are NOT ambiguous,
then subtracts from total to get ambiguous arrays.
"""

import sys

input = sys.stdin.readline
from math import gcd

n, m = map(int, input().split())
M = 998244353


c = 0           # Result counter for ambiguous arrays
a = m           # Tracks the number of valid sequences (used in inclusion-exclusion)
b = 1           # Tracks the LCM of indices that must be avoided due to gcd condition

for i in range(2, n + 1):
    if a != 0:
        # If current index and b are coprime, update b to be their LCM
        if gcd(b, i) == 1:
            b *= i
        # Divide a by b to reflect inclusion-exclusion effect
        a *= m // b
    # Add the difference between total sequences and non-ambiguous ones
    c += pow(m, i, M) - a % M
    c %= M
print(c)


# https://github.com/VaHiX/CodeForces/