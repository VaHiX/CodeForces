# Problem: CF 477 A - Dreamoon and Sums
# https://codeforces.com/contest/477/problem/A

"""
Code Purpose:
This code computes the sum of all "nice" integers based on the given parameters a and b.
An integer x is called nice if for some k in [1, a], the condition (x // k) % k == 0 holds.
The algorithm uses mathematical derivation to compute the result efficiently.

Algorithms/Techniques:
- Mathematical derivation to simplify the summation formula
- Modular arithmetic for large number handling
- Efficient computation using arithmetic series formulas

Time Complexity: O(1)
Space Complexity: O(1)

The derivation is based on rewriting the condition and summing over all valid combinations.
"""

MOD = int(1e9 + 7)
a, b = list(map(int, input().split()))
res = b * (b - 1) // 2 * (a + (1 + a) * a * b // 2)
print(res % MOD)


# https://github.com/VaHiX/CodeForces/