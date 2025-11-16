# Problem: CF 1942 G - Bessie and Cards
# https://codeforces.com/contest/1942/problem/G

"""
Code Purpose:
This code calculates the probability that Bessie wins the card game, given the number of "draw 0", "draw 1", and "draw 2" cards.
The solution uses combinatorics and inclusion-exclusion principles to compute the desired probability.

Algorithms/Techniques:
- Precomputed factorials and modular inverses for efficient binomial coefficient calculation
- Inclusion-exclusion principle to count valid card sequences
- Modular arithmetic using modulo 998244353

Time Complexity:
- Preprocessing: O(n) where n = 10^6 + 5
- Per test case: O(a + c) due to the loop over p

Space Complexity:
- O(n) for storing factorials and modular inverses
"""

def binom(n, k):
    # Compute binomial coefficient C(n, k) mod 998244353
    if k < 0 or k > n:
        return 0
    return fact[n] * inv[k] * inv[n - k] % 998244353


def ibinom(n, k):
    # Compute inverse of binomial coefficient C(n, k) mod 998244353
    if k < 0 or k > n:
        return 0
    return inv[n] * fact[k] * fact[n - k] % 998244353


# Precompute factorials and modular inverses
fact = [1]
for i in range(1, 10**6 + 5):
    fact.append(fact[-1] * i % 998244353)

inv = [pow(fact[-1], -1, 998244353)]
for i in range(10**6 + 4, 0, -1):
    inv.append(inv[-1] * i % 998244353)
inv.reverse()


# Process each test case
for _ in range(int(input())):
    a, b, c = map(int, input().split())
    # Calculate total paths with at least 5 special cards in first 5 draws
    paths = binom(a + c + 5, c) % 998244353
    ans = 0
    # Loop through possible values of p to compute valid sequences via inclusion-exclusion
    for p in range(4, a + c + 5, 2):
        q = 4
        x = (p + q) // 2
        y = (p - q) // 2
        # Compute terms for inclusion-exclusion
        k = (
            (x + 1 - y)
            * binom(x + y, x)
            * pow(x + 1, -1, 998244353)
            * binom(a + c - p + 4, a - (p - 4) // 2)
            % 998244353
        )
        paths -= k  # Subtract invalid cases
        ans += k * binom(p // 2 + 3, 5) % 998244353  # Add valid configurations
    ans += paths * binom(a + 5, 5)  # Add the final component for full probability
    # Final output: ans scaled by inverse binomial coefficients
    print(ans * ibinom(a + c + 5, c) * ibinom(a + 5, 5) % 998244353)


# https://github.com/VaHiX/CodeForces/