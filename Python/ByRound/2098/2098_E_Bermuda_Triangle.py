# Problem: CF 2098 E - Bermuda Triangle
# https://codeforces.com/contest/2098/problem/E

"""
E. Bermuda Triangle

Purpose:
Solves a problem where an airplane moves inside a triangular region (0,0), (0,n), (n,0) with a given velocity vector.
The airplane reflects off boundaries according to physics laws and escapes when hitting a vertex.
We determine if the plane escapes and count collisions before escape.

Algorithms/Techniques:
- Extended Euclidean Algorithm (for Bezout coefficients)
- Chinese Remainder Theorem (to solve systems of modular equations)
- Modular arithmetic for solving linear Diophantine equations
- GCD calculations

Time Complexity: O(log(min(vx, vy)) + log(n))
Space Complexity: O(1)

Input Format:
n, x, y, vx, vy: integers describing triangle size and motion parameters.

Output Format:
Number of boundary hits before escape, or -1 if never escapes.
"""

import sys
from math import gcd

input = sys.stdin.readline
MOD = 10**9 + 7


def bezout(a, b):
    """
    Given integers a and b, return a tuple (x, y, g),
    where x*a + y*b == g == gcd(a, b).
    Uses Extended Euclidean Algorithm.
    """
    u1, v1, r1 = 1, 0, a
    u2, v2, r2 = 0, 1, b
    while r2:
        q = r1 // r2
        u1, u2 = u2, u1 - q * u2
        v1, v2 = v2, v1 - q * v2
        r1, r2 = r2, r1 - q * r2
        assert u1 * a + v1 * b == r1
        assert u2 * a + v2 * b == r2
    if r1 < 0:
        u1, v1, r1 = -u1, -v1, -r1
    return (u1, v1, r1)


def crt(cong1, cong2):
    """
    Apply the Chinese Remainder Theorem to combine two congruences into one.
    Each congruence is given as (remainder, modulus).
    Returns a single equivalent congruence (a, n).
    Raises ValueError if congruences are incompatible.
    """
    a1, n1 = cong1
    a2, n2 = cong2
    c1, c2, g = bezout(n1, n2)
    assert n1 * c1 + n2 * c2 == g
    if (a1 - a2) % g != 0:
        raise ValueError(f"Incompatible congruences {cong1} and {cong2}.")
    lcm = n1 // g * n2
    rem = (a1 * c2 * n2 + a2 * c1 * n1) // g
    return rem % lcm, lcm


def read_array(factory):
    return [factory(num) for num in input().strip().split()]


def print_array(arr):
    print(" ".join(map(str, arr)))


def solve(n, x, y, vx, vy):
    # Normalize velocity vector by dividing by GCD
    g = gcd(vx, vy)
    vx //= g
    vy //= g

    # Check if escape is possible based on divisibility conditions.
    # If the initial point is not reachable, return -1 early.
    if x % gcd(vx, n) != 0:
        return -1
    if y % gcd(vy, n) != 0:
        return -1

    # Solve for time to reach each side boundary and determine
    # which boundary points are hit by the line equation from
    # current position with given velocity.
    gx = gcd(vx, n)
    cx = (-(x // gx)) * pow(vx // gx, -1, n // gx) % (n // gx)
    gy = gcd(vy, n)
    cy = (-(y // gy)) * pow(vy // gy, -1, n // gy) % (n // gy)

    # Apply CRT to find a common time t such that 
    # t ≡ cx mod (n//gx) and t ≡ cy mod (n//gy)
    g = gcd(n // gx, n // gy)
    if cx % g != cy % g:
        return -1
    c, cmod = crt((cx, n // gx), (cy, n // gy))

    # Adjust time to be positive
    if c == 0:
        c += cmod

    # Determine number of horizontal and vertical steps taken.
    hor = (c * vy) // n
    ver = (c * vx) // n

    # Count diagonal hits using absolute difference.
    adi = abs((y + c * vy) + (x + c * vx)) // (2 * n)
    dia = abs((y + c * vy) - (x + c * vx)) // (2 * n)

    return hor + ver + adi + dia


if __name__ == "__main__":
    t = int(input())
    for _ in range(t):
        n, x, y, vx, vy = read_array(int)
        ans = solve(n, x, y, vx, vy)
        print(ans)


# https://github.com/VaHiX/codeForces/