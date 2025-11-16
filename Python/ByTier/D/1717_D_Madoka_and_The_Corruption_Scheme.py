# Problem: CF 1717 D - Madoka and The Corruption Scheme
# https://codeforces.com/contest/1717/problem/D

"""
Code Purpose:
This code solves the problem of finding the minimum possible number of the winner in a tournament
where sponsors can change up to k match outcomes. It uses combinatorial mathematics to compute
the minimal winning participant number that is guaranteed regardless of the sponsor changes.

Algorithms/Techniques:
- Combinatorial mathematics and modular arithmetic
- Lucas' theorem or direct computation with modular inverse
- Prefix sum of binomial coefficients

Time Complexity: O(k * log(MOD)) where MOD = 10^9 + 7
Space Complexity: O(1) - only using a few variables for computation

The solution computes the sum of binomial coefficients C(n, i) for i from 1 to k,
which represents the number of ways to choose up to k changes from n matches.
This sum modulo MOD gives us the minimum guaranteed winner number.
"""

MOD = 10**9 + 7

n, k = map(int, input().split())
if n <= k:
    # If number of rounds is less than or equal to number of allowed changes,
    # then all participants can be potentially made winners by flipping matches.
    print((2**n) % MOD)
else:
    # Initialize result and binomial coefficient
    rec = 1  # Start with C(n, 0) = 1
    c = 1    # This will hold current binomial coefficient C(n, i)
    
    # Calculate sum of binomial coefficients from C(n, 1) to C(n, k)
    for i in range(1, k + 1):
        # Compute C(n, i) = C(n, i-1) * (n - i + 1) / i using modular inverse
        c = (c * (n - i + 1) * pow(i, -1, MOD)) % MOD
        rec = (rec + c) % MOD  # Add to result
        
    print(rec)


# https://github.com/VaHiX/CodeForces/