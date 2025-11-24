# Problem: CF 1808 E3 - Minibuses on Venus (hard version)
# https://codeforces.com/contest/1808/problem/E3

"""
Purpose: This code computes the number of "lucky" tickets on Venus, where a ticket is lucky if one digit equals 
         the sum of the remaining digits modulo k. The solution uses mathematical insights and modular exponentiation 
         to handle large values of n (up to 10^18).

Algorithms/Techniques:
- Modular exponentiation (using pow with 3 arguments)
- GCD computation (math.gcd)
- Mathematical simplification based on parity of k and properties of sums in modular arithmetic
- Handling edge cases for odd vs even k

Time Complexity: O(log n + log k) due to modular exponentiation and GCD calculation.
Space Complexity: O(1) - only a few variables are used.
"""

import math

n, k, m = map(int, input().split())
ans = 0
if k % 2 == 1:
    # For odd k, use a specific formula derived from the mathematical properties
    print((pow(k, n, m) - pow(k - 1, n, m) + (-1) ** n * (1 - math.gcd(n - 2, k))) % m)
else:
    # For even k, use another formula adjusted for the even case
    print(
        (
            pow(k // 2, n, m)
            - pow(k // 2 - 1, n, m)
            + (-1) ** n * (1 - math.gcd(n - 2, k // 2))
        )
        * pow(2, n - 1, m)
        % m
    )


# https://github.com/VaHiX/CodeForces/