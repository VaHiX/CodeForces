# Problem: CF 1912 J - Joy of Pokémon Observation
# https://codeforces.com/contest/1912/problem/J

"""
Joy of Pok´emon Observation

Purpose:
This code solves a problem where given a total number of limbs `t` and `s` species with their respective limb counts,
we need to count how many combinations of Pok´emon (of those species) can add up to exactly `t` limbs.
The approach handles cases for s=1, s=2, and s=3 species separately.

Algorithms/Techniques:
- For s=1: Direct division check if t is divisible by the limb count.
- For s=2: Enumerate possible multiples of first species, use helper function `f()` to calculate combinations
           for remaining limbs using second species.
- For s=3: Use inclusion-exclusion principle / generating functions with modulo arithmetic.

Time Complexity:
- O(1) for s=1,
- O(log(t)) for s=2 (since t is at most 1e9 but loop limited to 16),
- O(d) for s=3, where d is a bounded factor derived from least common multiples.

Space Complexity:
- O(1), constant extra space.
"""

from math import gcd


def f(t, a, b):
    """Helper function to compute combinations for two species given t total limbs."""
    if t < 0:
        return 0
    c = a // gcd(a, b)  # Compute LCM of a and b, simplified to avoid large numbers
    for i in range(16):  # Limit loop to 16 iterations due to small limb counts (max 16)
        if t - i * a < 0:
            break
        if (t - i * a) % b == 0:  # Check if remaining limbs divisible by b
            return (t - i * a) // b // c + 1  # Return number of valid combinations after normalization
    return 0


def solve():
    A = list(map(int, input().split()))
    t = A[0]
    s = A[1]
    A = A[2:]
    
    if s == 1:
        # Direct case: only one species, must be divisible by limb count
        if t % A[0] == 0:
            print(1)
        else:
            print(0)
        return
    
    elif s == 2:
        # Two species: iterate through multiples and compute using f()
        a, b = A
        print(f(t, a, b))
    
    else:
        # Three species using inclusion-exclusion or brute-force over one variable
        a, b, c = A
        d = b * c // gcd(b, c)  # LCM of b and c
        dd = a * d // (gcd(a, d))  # LCM of a and d
        res = 0
        for i in range(d // (gcd(a, d))):  # Loop up to LCM of all limbs mod GCD(a, d)
            if t - i * a < 0:
                break
            cur = f(t - i * a, b, c)  # Get combinations from second two species for leftover limbs
            if cur == 0:
                continue
            q = (t - i * a) // dd  # Quotient in terms of LCM of all three
            # Apply arithmetic progression sum formula to get total valid combinations
            res += (cur + cur - q * dd // d) * (q + 1) // 2
        print(res)


for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/codeForces/