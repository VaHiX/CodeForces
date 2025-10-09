# Problem: CF 2025 E - Card Game
# https://codeforces.com/contest/2025/problem/E

"""
E. Card Game

Purpose:
This code calculates the number of ways to distribute a deck of n×m cards between two players such that the first player wins. 
The game rules define which cards can beat others based on suit and rank.
The solution uses dynamic programming with convolution and exponentiation by squaring to compute transitions efficiently.

Algorithms/Techniques:
- Dynamic Programming with convolution
- Fast exponentiation (binary exponentiation)
- Modular arithmetic
- Transition matrix exponentiation

Time Complexity: O(m^2 * log(n)) where m is the rank count and n is the suit count.
Space Complexity: O(m^2) for storing DP arrays and convolution results.

"""

MOD = 998244353
n, m = map(int, input().split())


def convolution(P, Q):
    # Convolution of two polynomials P and Q
    # Used for efficiently computing transitions in DP
    assert len(P) == len(Q)
    R = []
    for i in range(len(P)):
        suma = 0
        for j in range(i + 1):
            suma += P[j] * Q[i - j]
            suma %= MOD
        R.append(suma)
    return R


def power(P, k):
    # Fast exponentiation of a polynomial P to the power k
    # Used to compute transition matrix k times
    R = [0] * len(P)
    R[0] = 1
    while k:
        if k & 1:
            R = convolution(R, P)
        P = convolution(P, P)
        k >>= 1
    return R


# Initialize DP array for transitions
dp = [1] + [0] * m
for _ in range(m):
    prev = dp
    dp = [0] * (m + 1)
    for c in range(m + 1):
        if c - 1 >= 0:
            dp[c] += prev[c - 1]
        if c + 1 <= m:
            dp[c] += prev[c + 1]
        dp[c] %= MOD

# Compute the result using exponentiation
dpp = power(dp, n - 1)
ans = sum(dp[m] * dpp[m] % MOD for m in range(m + 1)) % MOD
print(ans)


# https://github.com/VaHiX/codeForces/