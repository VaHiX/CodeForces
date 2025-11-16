# Problem: CF 1712 E1 - LCM Sum (easy version)
# https://codeforces.com/contest/1712/problem/E1

"""
Algorithm: Count triplets (i,j,k) such that l <= i < j < k <= r and lcm(i,j,k) >= i + j + k.
Technique: 
- Use inclusion-exclusion principle with prime counting and LCM properties.
- Precompute divisors using a sieve-like method.
- For each i, calculate contribution of valid triplets and subtract invalid ones.
Time Complexity: O(r log r) due to sieve-like operations and iteration over divisors.
Space Complexity: O(r) for the array V to store divisor counts.
"""

import sys

input = sys.stdin.readline

for _ in range(int(input())):
    l, r = map(int, input().split())
    V = [0 for _ in range(r + 1)]
    sol = 0
    # For each i in range [l, r], compute how many valid triplets include i
    for i in range(l, r + 1):
        # Add all triplets (i,j,k) where i < j < k and j,k > i
        # This counts all combinations of (j,k) from (i+1) to r, which is C(r-i, 2)
        sol += ((r - i) * (r - i - 1)) // 2
        # Increment the divisor count for all multiples of i
        for j in range(i + i, r + 1, i):
            V[j] += 1
        # Subtract the invalid triplets where lcm(i,j,k) < i + j + k
        # This uses the formula for combinations with repetition
        sol -= (V[i] * V[i] - V[i]) // 2
    # Handle specific cases for small values
    # If i+j+k is divisible by 2 and 3, and also by small k, adjust count
    for i in range(l, 2 * r + 1):
        if i % 2 == 0:
            if i % 3 == 0:
                for k in range(4, 6):
                    if i % k == 0:
                        if i // k >= l:
                            sol -= 1
    print(sol)


# https://github.com/VaHiX/CodeForces/