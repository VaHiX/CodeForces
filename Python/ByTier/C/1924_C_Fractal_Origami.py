# Problem: CF 1924 C - Fractal Origami
# https://codeforces.com/contest/1924/problem/C

"""
Fractal Origami Problem Solution
Algorithm: 
- The problem simulates a fractal folding process on a square paper.
- Each operation folds the corners to the center, creating a new square with half the side length.
- After N operations, we analyze the crease lines (mountain and valley).
- The ratio M/V can be expressed in the form A + B * sqrt(2), where A and B are rational.
- The task is to compute the value of B as an irreducible fraction p/q, and return p * inv(q) mod 999999893.

Time Complexity: O(log N) per test case due to modular exponentiations.
Space Complexity: O(1) - only using a constant amount of extra space.
"""

def II():
    return int(input())


def LMI():
    return list(map(int, input().split()))


def I():
    return input()


def MII():
    return map(int, input().split())


import sys

input = sys.stdin.readline
mod = 999999893

for _ in range(II()):
    n = II()
    if n % 2:  # If n is odd
        # Calculate beta = 2^((n-1)/2) - 1
        beta = pow(2, (n - 1) // 2, mod) - 1
        # Calculate alpha = beta + 2
        alp = beta + 2
        # Compute (beta * inverse((alp^2 - 2) mod mod)) mod mod
        # This computes the B coefficient in the form A + B*sqrt(2)
        print(beta * pow((alp**2 - 2) % mod, -1, mod) % mod)
    else:  # If n is even
        # Calculate alpha = 2^((n-2)/2) - 1
        alp = pow(2, (n - 2) // 2, mod) - 1
        # Calculate beta = alpha + 1
        bet = alp + 1
        # Compute (-(alpha + beta) * inverse((2 * alpha^2 - 1) mod mod)) mod mod
        # This computes the B coefficient for even n cases
        print(((-(alp + bet)) % mod) * pow((2 * alp**2 - 1) % mod, -1, mod) % mod)


# https://github.com/VaHiX/CodeForces/