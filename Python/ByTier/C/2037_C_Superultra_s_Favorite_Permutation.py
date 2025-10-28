# Problem: CF 2037 C - Superultra's Favorite Permutation
# https://codeforces.com/contest/2037/problem/C

"""
Problem: Construct a permutation of length n such that the sum of every two adjacent elements is composite.
Algorithm/Technique: Pattern-based construction
Time Complexity: O(n) per test case
Space Complexity: O(n) for output array

The solution uses a precomputed pattern for n > 5. For small n (n <= 5), it's impossible to construct such a permutation.
For larger n, we use a specific arrangement to ensure all adjacent sums are composite.
"""

for n in [*open(0)][1:]:
    n = int(n) + 1
    # For n <= 5, it's impossible to construct a valid permutation
    # For n > 5, we use a pattern that ensures all adjacent sums are composite
    print(*[[-1], [1, 3, *range(7, n, 2), 5, 4, 2, *range(6, n, 2)]][n > 5])


# https://github.com/VaHiX/CodeForces/