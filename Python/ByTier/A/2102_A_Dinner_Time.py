# Problem: CF 2102 A - Dinner Time
# https://codeforces.com/contest/2102/problem/A

"""
Problem: Dinner Time

Purpose:
This code determines whether there exists an integer array of length n such that:
1. The total sum of all elements equals m.
2. The sum of every p consecutive elements equals q.

Algorithms/Techniques:
- Mathematical analysis to check consistency of constraints
- Modular arithmetic and division to validate feasibility

Time Complexity: O(1) per test case
Space Complexity: O(1)

The key insight is:
- If we have n elements and each group of p consecutive elements sums to q,
  then there are (n - p + 1) such groups.
- If all these group sums are equal to q, the total can be calculated as:
  q * (n // p) if n is divisible by p, or q * (n // p) + q * (n % p) if not.
  But more carefully, we use: total sum m = q * number_of_full_groups,
  which helps us derive necessary conditions.

"""

import sys

input = sys.stdin.readline
for i in range(int(input())):
    n, m, p, q = map(int, input().split())
    # Check if the given constraints are consistent:
    # We can construct an array if either:
    # - n is not divisible by p (meaning there's a remainder that still needs to be handled)
    #   or
    # - the full groups contribute exactly m when multiplied by q.
    print("yes" if n % p or q * (n // p) == m else "no")


# https://github.com/VaHiX/codeForces/