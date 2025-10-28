# Problem: CF 1951 G - Clacking Balls
# https://codeforces.com/contest/1951/problem/G

"""
Code Purpose:
This code solves the "G. Clacking Balls" problem, which involves calculating the expected number of operations required to reduce n balls to 1 ball in m baskets arranged in a circle. Each operation, chosen uniformly at random, moves a ball to the next basket clockwise, and if that basket is occupied, the occupying ball is removed.

The solution uses a mathematical approach based on expected value and the concept of pairwise distances in a circular arrangement:
- Sorts initial ball positions.
- Calculates sum of cubes of distances between adjacent balls (considering circular wrap-around).
- Uses the formula derived from the mathematical expectation to compute final result.

Algorithms/Techniques:
- Sorting
- Modular arithmetic and modular inverse
- Mathematical expectation calculation using sum of cubes of distances in circular arrangement

Time Complexity: O(n log n) due to sorting, where n is the number of balls.
Space Complexity: O(n) for storing the initial positions.

"""

import sys

P = 1000000007  # Modulo value (10^9 + 7)


def mod_inv(x, mod=P):
    """Calculate modular inverse of x mod P using Fermat's little theorem."""
    return pow(x, mod - 2, mod)


def solve_case(it):
    # Read n and m
    n = next(it)
    m = next(it)
    # Read initial positions of balls
    a = [next(it) for _ in range(n)]
    
    # Sort the positions
    a.sort()
    
    # Precompute m^3 mod P
    m3 = (m * m) % P
    m3 = (m3 * m) % P
    
    # Compute sum of cubes of distances
    sum_d3 = 0
    for i in range(n):
        if i == n - 1:
            # Distance from last to first ball (circular wrap-around)
            d = a[0] - a[i] + m
        else:
            # Normal distance between adjacent balls
            d = a[i + 1] - a[i]
        d_mod = d % P  # Ensure d is within mod range
        sum_d3 = (sum_d3 + d_mod * d_mod % P * d_mod) % P  # Add cube of distance
    
    # Compute numerator using derived formula
    ans = (m3 - sum_d3) % P
    
    # Compute final result using modular inverse
    inv6 = mod_inv(6)  # Modular inverse of 6
    inv_m = mod_inv(m % P)  # Modular inverse of m
    ans = ans * inv6 % P  # Multiply by 1/6
    ans = ans * inv_m % P  # Multiply by 1/m
    ans = ans * (n % P) % P  # Multiply by n
    
    return ans


def main():
    data = list(map(int, sys.stdin.buffer.read().split()))
    it = iter(data)
    t = next(it)
    out_lines = []
    for _ in range(t):
        out_lines.append(str(solve_case(it)))
    sys.stdout.write("\n".join(out_lines))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/