# Problem: CF 1925 F - Fractal Origami
# https://codeforces.com/contest/1925/problem/F

"""
Code Purpose:
This program calculates the ratio M/V of mountain to valley crease lines after N operations of folding a square paper,
where each operation folds the corners to the center. The result is expressed in the form A + B*sqrt(2), and the task
is to output B in the form of an irreducible fraction p/q, then compute p * inverse(q) mod 999999893.

Algorithms/Techniques:
- Modular exponentiation to compute powers modulo MOD
- Modular inverse using Fermat's little theorem (since MOD is prime)
- Mathematical recurrence relation for the computation of M and V

Time Complexity: O(log N) per test case due to modular exponentiation
Space Complexity: O(1) - only using a constant amount of extra space
"""

MOD = 999999893


def inverse(x):
    # Using Fermat's little theorem: a^(p-1) ≡ 1 (mod p) => a^(-1) ≡ a^(p-2) (mod p)
    return pow(x, MOD - 2, MOD)


t = int(input())
for i in range(t):
    n = int(input())
    # Compute terms using modular exponentiation
    a = c = (pow(2, n // 2 + 1, MOD) - 2) % MOD
    b = d = (pow(2, (n - 1) // 2 + 1, MOD) - 2) % MOD
    b = (b + 2) % MOD
    # Apply formula to calculate the required value
    ans = (a * d - b * c) * inverse(a * a - 2 * b * b) % MOD
    print(ans)


# https://github.com/VaHiX/CodeForces/