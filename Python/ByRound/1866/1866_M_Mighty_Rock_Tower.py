# Problem: CF 1866 M - Mighty Rock Tower
# https://codeforces.com/contest/1866/problem/M

"""
Code Purpose:
This code computes the expected number of moves required to build a rock tower of height N,
accounting for the probability of rocks falling during construction. The solution uses dynamic programming
with probability calculations and modular arithmetic.

Algorithms/Techniques:
- Dynamic Programming
- Probability calculation and modular inverse
- Preprocessing probabilities for efficient computation

Time Complexity: O(N * 100) = O(N)
Space Complexity: O(N + 100) = O(N)
"""

mod = 998244353
n = int(input())
s = list(map(int, input().split()))
inv = pow(100, mod - 2, mod)  # Compute modular inverse of 100
p = [0] * 100
invp = [0] * 100
for i in range(100):
    p[i] = i * inv % mod  # Convert percentage to probability
    invp[i] = pow(1 - p[i], mod - 2, mod)  # Modular inverse of (1 - p[i])

a = [0] * 100
ans = [0] * n
for i in range(n):
    if i >= 1:
        # Accumulate probabilities from previous state
        for j in range(100):
            a[j] = (a[j] + ans[i - 1]) * p[j] % mod
    # Compute expected value for current height using recurrence relation
    ans[i] = 1 + p[s[i]] * (1 + a[s[i]]) * invp[s[i]] % mod

# Output total expected moves
print(sum(ans) % mod)


# https://github.com/VaHiX/CodeForces/