# Problem: CF 2125 C - Count Good Numbers
# https://codeforces.com/contest/2125/problem/C

# ==============================================================================
# Problem: Count Good Numbers
# Purpose: Given a range [l, r], count how many numbers in that range have all
#          prime factors with at least two digits (i.e., >= 10).
#
# Algorithm: Inclusion-Exclusion Principle
# - We define good numbers as those whose prime factors are all >= 10.
# - The complement is the set of numbers divisible by any of {2, 3, 5, 7}.
# - Using inclusion-exclusion principle on primes 2, 3, 5, 7 to compute:
#   count of numbers in [1, n] with at least one small prime factor.
# - Then subtract from total: f(n) = n - (count of bad numbers up to n)
# - For a range [l, r]: answer = f(r) - f(l-1)
#
# Time Complexity: O(1) per query — constant time due to fixed number of primes
# Space Complexity: O(1) — only uses fixed-size variables and expressions
# ==============================================================================

f = (
    lambda n: n
    - n // 2      # Subtract multiples of 2
    - n // 3      # Subtract multiples of 3
    - n // 5      # Subtract multiples of 5
    - n // 7      # Subtract multiples of 7
    + n // 6      # Add back multiples of 2*3 (since counted twice)
    + n // 10     # Add back multiples of 2*5
    + n // 14     # Add back multiples of 2*7
    + n // 15     # Add back multiples of 3*5
    + n // 21     # Add back multiples of 3*7
    + n // 35     # Add back multiples of 5*7
    - n // 30     # Subtract multiples of 2*3*5 (counted too many times)
    - n // 42     # Subtract multiples of 2*3*7
    - n // 70     # Subtract multiples of 2*5*7
    - n // 105    # Subtract multiples of 3*5*7
    + n // 210    # Add back multiples of 2*3*5*7 (full inclusion)
)

# Process input and compute result for each test case
for s in [*open(0)][1:]:
    a, b = map(int, s.split())
    print(f(b) - f(a - 1))


# https://github.com/VaHiX/codeForces/