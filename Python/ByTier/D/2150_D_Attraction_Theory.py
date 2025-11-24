# Problem: CF 2150 D - Attraction Theory
# https://codeforces.com/contest/2150/problem/D

"""
D. Attraction Theory

Purpose:
This code calculates the sum of scores over all possible distinct position arrays that can be formed by placing attractions at various integer coordinates on a 1D axis. Each person moves towards the attraction and adjusts their position accordingly. The score is based on values at each final position.

Algorithms/Techniques:
- Preprocessing factorials and inverse factorials for combination calculations
- Difference array techniques for efficient range updates
- Mathematical combinatorics to count valid configurations

Time Complexity: O(MAX + n^2) where MAX = 207486 and n is the input size.
Space Complexity: O(MAX + n) due to precomputed arrays and temporary structures.

Input:
Each test case contains:
- An integer n (number of people)
- An array a of n integers (values at each position)

Output:
Sum of scores over all possible distinct position arrays modulo 998244353.
"""

MAX = 207486
MOD = 998244353
fact = [1] * MAX  # Precompute factorials
for i in range(1, MAX):
    fact[i] = fact[i - 1] * i % MOD

anti = [1] * MAX  # Precompute inverse factorials
anti[-1] = pow(fact[-1], -1, MOD)
for i in range(MAX - 2, -1, -1):
    anti[i] = anti[i + 1] * (i + 1) % MOD

def cmb(n, k):  # Fast combination calculation using precomputed values
    return anti[k] * anti[n - k] * fact[n] % MOD if 0 <= k <= n else 0

for _ in range(int(input())):
    n = int(input())
    score = [int(t) for t in input().split()]
    pacc = [0] * (n + 2)  # Difference array for accumulating contributions to positions
    part = [0] * (n + 1)  # Another difference array for tracking partial sums
    
    # Iterate through all possible lengths L of segments to analyze
    for L in range(2, n + 1):
        off = n + 1 - L  # Offset to calculate the range boundaries
        
        if (n - L) % 2 == 0:  # L is even in terms of segment construction
            w = cmb((n - L) // 2 + L - 1, L - 1)  # Combinatorial coefficient for even case
            w2 = cmb((n - L) // 2 - 1 + L - 1, L - 1)  # Another combinatorial coefficient
            
            c = w * n * pow(L, -1, MOD) % MOD  # Contribution calculation with modular inverse
            c += w2 * (n - 2) * pow(L, -1, MOD) % MOD
            
            # Range update using difference array technique
            pacc[0] += c
            pacc[L] -= c
            pacc[off + 0] -= c
            pacc[off + L] += c
            
            part[0] += w2  # Update another differential array for further adjustments
            part[L - 1] += w2
            part[off + 0] -= w2
            part[off + L - 1] -= w2
        else:  # L is odd in terms of segment construction
            w = cmb((n - 1 - L) // 2 + L - 1, L - 1)  # Combinatorial coefficient for odd case
            
            c = 2 * w * (n - 1) * pow(L, -1, MOD) % MOD  # Contribution calculation for odd length
            
            # Range updates again for odd segment
            pacc[0] += c
            pacc[L] -= c
            pacc[off + 0] -= c
            pacc[off + L] += c

            part[0] += w
            part[L - 1] += w
            part[off + 0] -= w
            part[off + L - 1] -= w

    # Apply prefix sums to difference arrays to reconstruct actual contribution counts
    for i in range(n):
        pacc[i + 1] += pacc[i]
    
    for i in range(n):
        part[i] += pacc[i]

    for i in range(n):
        part[i + 1] += part[i]
    
    # Compute final score
    S = 0
    for i in range(n):
        S += (n + part[i]) * score[i]
        
    print(S % MOD)


# https://github.com/VaHiX/CodeForces/