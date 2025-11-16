# Problem: CF 871 A - Maximum splitting
# https://codeforces.com/contest/871/problem/A

"""
Algorithm: Maximum Splitting into Composite Numbers

This solution determines the maximum number of composite summands that can be used to represent a given number n.
A composite number is an integer greater than 1 that is not prime (i.e., has divisors other than 1 and itself).

Key Observations:
1. The smallest composite number is 4.
2. All integers greater than 11 can be represented as a sum of composite numbers using a greedy approach:
   - If n is even, we can write it as a sum of 4s.
   - If n is odd, we can use one 9 (composite) and the rest as 4s.
3. Numbers 1, 2, 3, 5, 7, 11 cannot be represented as sums of composite numbers because they are either prime or less than the smallest composite (4).

Approach:
- For n <= 11, check if n is one of {2, 5, 7, 11}, return -1 if so.
- For n > 11, compute the maximum number of composites as (n // 4) - (n % 2).
  - This works because we try to use as many 4s as possible, and adjust with one 9 if necessary for odd numbers.

Time Complexity: O(1) per query
Space Complexity: O(1)
"""

for n in [*open(0)][1:]:
    n = int(n)
    # Check if n is in the set of impossible values
    print(-1 if n in [2, 5, 7, 11] else n // 4 - n % 2)


# https://github.com/VaHiX/CodeForces/