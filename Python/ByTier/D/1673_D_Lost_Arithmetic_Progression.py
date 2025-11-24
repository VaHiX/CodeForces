# Problem: CF 1673 D - Lost Arithmetic Progression
# https://codeforces.com/contest/1673/problem/D

"""
Problem: Lost Arithmetic Progression

Given two finite arithmetic progressions B and C, where C contains all elements common to both A and B,
we need to determine how many different finite arithmetic progressions A could have existed.

Key observations:
- Since C is the intersection of A and B, every element in C must be in both A and B.
- Elements in A must follow an arithmetic sequence with a common difference that divides the common difference of B.
- Similarly, elements in A must align with elements in B such that their intersection forms C.
- If the constraints are too loose (e.g., A can be arbitrarily extended), there are infinitely many solutions.

Approach:
1. Check if any trivial impossible cases exist:
   - Common differences don't align (r % q != 0)
   - First elements don't align (c - b) % q != 0
   - Ranges do not overlap properly in terms of bounds

2. Use mathematical properties related to divisors and GCDs to count valid progressions efficiently.

Time Complexity: O(√r * log(min(q, r))) per test case.
Space Complexity: O(1).
"""

t = int(input())
mod = 10**9 + 7
from math import gcd

for _ in range(t):
    b, q, y = map(int, input().split())  # b: first term, q: common difference, y: number of terms of B
    c, r, z = map(int, input().split())  # c: first term, r: common difference, z: number of terms of C
    
    # If r does not divide q, then there can't be any valid A
    if r % q != 0:
        print(0)
    # If the first term of C does not align properly with B, no valid A
    elif (c - b) % q != 0:
        print(0)
    # If B does not contain C fully, no valid A
    elif b > c or b + (y - 1) * q < c + (z - 1) * r:
        print(0)
    # If we are in a situation with potentially infinite progressions
    elif b > c - r or b + (y - 1) * q < c + (z - 1) * r + r:
        print(-1)
    else:
        ans = 0
        # Iterate through all divisors of r
        for i in range(1, 10**5):
            if i * i > r:
                break
            if r % i == 0:
                # Check if this divisor meets the GCD condition
                if gcd(i, q) * r == i * q:
                    # Add contribution from this divisor
                    ans += (r // i) * (r // i) % mod
                    ans %= mod
            if i * i == r:
                break
            j = r // i
            if r % j == 0:
                if gcd(j, q) * r == j * q:
                    ans += (r // j) * (r // j) % mod
                    ans %= mod
        print(ans)


# https://github.com/VaHiX/CodeForces/