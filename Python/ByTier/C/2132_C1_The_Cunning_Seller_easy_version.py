# Problem: CF 2132 C1 - The Cunning Seller (easy version)
# https://codeforces.com/contest/2132/problem/C1

"""
C1. The Cunning Seller (easy version)

Purpose:
This code computes the minimum cost to buy exactly `n` watermelons using a greedy approach based on the optimal deal structure.
Each deal allows selling 3^x watermelons for 3^(x+1) + x * 3^(x-1) coins.
The algorithm converts the number `n` into base 3 and uses dynamic programming to calculate the minimal cost.

Algorithms/Techniques:
- Base-3 representation of numbers
- Dynamic Programming with precomputed powers of 3
- Greedy selection for minimal cost per unit watermelon

Time Complexity: O(log n) per test case, due to base-3 digit processing.
Space Complexity: O(1), since we use a fixed-size array P (precomputed up to 40 powers of 3).

"""

import sys

_, *A = map(int, sys.stdin.read().split())
P = [1]  # Precompute powers of 3: 3^0, 3^1, ..., 3^40
for tc in range(40):
    P += (P[-1] * 3,)  # Build array of powers of 3

for n in A:
    r = i = 0
    while n:
        d = n % 3      # Get the base-3 digit at current position
        # Compute cost for this digit using precomputed values
        r += d * (P[i + 1] + (i and i * P[i - 1]))
        n //= 3        # Move to next digit
        i += 1         # Increment position
    print(r)


# https://github.com/VaHiX/codeForces/