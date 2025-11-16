# Problem: CF 1737 E - Ela Goes Hiking
# https://codeforces.com/contest/1737/problem/E

"""
Code Purpose:
This code calculates the survival probability for each ant in a line when they move randomly left or right on a stick, 
and annihilate each other based on weight and direction. The computation uses dynamic programming with precomputed 
powers of 1/2 modulo 10^9 + 7.

Algorithms/Techniques:
- Dynamic Programming
- Modular Arithmetic
- Precomputation of powers of 1/2

Time Complexity: O(n) per test case
Space Complexity: O(n) for precomputed powers and the line array
"""

MOD = 0x3B9ACA07
HALF = pow(2, -1, MOD)  # Modular inverse of 2
H = [1]
for _ in range(1_000_001):
    H.append(H[-1] * HALF % MOD)  # Precompute powers of 1/2

for _ in range(int(input())):
    n = int(input())

    line = [0] * n
    line[-1] = H[(n - 1) // 2]  # Base case: last ant's survival probability
    S = 0
    for i in range(n - 2, 0, -1):  # Iterate backwards from second last to second ant
        if 2 * i + 1 < n:  # Check bounds for left child
            S += line[2 * i + 1]
        if 2 * i + 2 < n:  # Check bounds for right child
            S += line[2 * i + 2]
        # Compute survival probability for ant at index i
        line[i] = H[i // 2 + 1] * (1 - S) % MOD

    for g in line:
        print(g)


# https://github.com/VaHiX/CodeForces/