# Problem: CF 2090 F1 - Key of Like (Easy Version)
# https://codeforces.com/contest/2090/problem/F1

"""
Algorithm: Dynamic Programming with Probability Calculation
Time Complexity: O(l * n^2) per test case
Space Complexity: O(n) per test case

This problem models a probabilistic game where n players take turns selecting keys to unlock l locks.
Each player chooses the key-lock pair that maximizes the probability of success based on remaining possibilities.
The solution computes the expected number of successful matches for each player using dynamic programming and
probability calculations.

Key techniques:
- Dynamic Programming with state tracking of probabilities
- Modular inverse for fraction arithmetic
- Probability update at each step based on optimal choice
"""

import sys

input = sys.stdin.readline
MOD = 10**9 + 7
for _ in range(int(input())):
    n, l, k = map(int, input().split())
    tot = l
    mov = [0] * n  # Probability distribution of current state
    mov[0] = 1     # Initially, first player has full probability
    out = [0] * n  # Expected number of successful matches for each player
    
    # Iterate backwards from l to 1 (number of remaining locks)
    for i in range(l, 0, -1):
        p = pow(i, -1, MOD)  # Modular inverse of i, used for uniform probability
        i %= n               # Reduce i mod n to avoid index overflow
        if i == 0:
            break
        
        nex = [0] * n        # Next state probabilities
        # For each possible current state (u), compute next state by choosing a key
        for u in range(n):
            # Try all possible choices up to current i locks
            for j in range(1, i + 1):
                nex[u] += mov[u - j] * p   # Add probability of transitioning from u-j to u
                nex[u] %= MOD
        mov = nex               # Update probabilities
        
        # Accumulate expected values for all positions
        for i in range(n):
            out[i - 1] += mov[i]
    
    # Normalize expected values to full total l
    for i in range(n):
        out[i] %= MOD
    
    # Calculate excess (remaining part) and distribute evenly among players
    ex = tot - sum(out)
    ex %= MOD
    ex *= pow(n, -1, MOD)  # Distribute the remainder evenly
    ex %= MOD
    
    # Add expected excess to output values
    for i in range(n):
        out[i] += ex
        out[i] %= MOD
    
    print(*out)


# https://github.com/VaHiX/codeForces/