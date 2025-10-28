# Problem: CF 2082 C - Math Division
# https://codeforces.com/contest/2082/problem/C

"""
C. Math Division
Purpose: Calculates the expected number of operations to reduce a binary number x to 1,
         where each operation is either floor(x/2) or ceil(x/2) with equal probability.
Approach:
    - For each bit in the binary representation of x, we compute the contribution to the expected number of steps.
    - The recurrence relation uses dynamic programming with memoization.
    - Modular arithmetic and modular inverse are used for computation under modulo 10^9 + 7.

Time Complexity: O(MAX_N) where MAX_N = 10^5
Space Complexity: O(MAX_N) for precomputed powers and DP table.

Algorithms/Techniques:
    - Dynamic Programming
    - Modular Arithmetic
    - Precomputation of Powers
"""

import sys

input = sys.stdin.readline


def main():
    MOD = 10**9 + 7
    BASE = 500000004  # Modular inverse of 2 modulo (10^9 + 7)
    MAX_N = 10**5
    power = [1] * MAX_N  # Precompute powers of BASE mod MOD
    for i in range(1, MAX_N):
        power[i] = (power[i - 1] * BASE) % MOD
    t = int(input().strip())
    for _ in range(t):
        n = int(input().strip())
        m = int(input().strip(), 2)  # Convert binary string to integer
        # Final computation using precomputed powers
        print((n - 2 + m * power[n - 1]) % MOD)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/codeForces/