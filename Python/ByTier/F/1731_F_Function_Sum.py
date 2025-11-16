# Problem: CF 1731 F - Function Sum
# https://codeforces.com/contest/1731/problem/F

"""
Code Purpose:
This code calculates the sum of f(a) over all arrays a of size n such that 1 <= a_i <= k,
where f(a) is the sum of all a_i such that position i is "good" in array a.
A position i is good if lsl(i) < grr(i), where lsl(i) counts elements before i that are smaller,
and grr(i) counts elements after i that are greater.

Algorithms/Techniques:
- Mathematical formula derivation using combinatorics and algebraic manipulation
- Efficient summation using closed-form expressions
- Modular arithmetic for large numbers

Time Complexity: O(n)
Space Complexity: O(1)

The derivation uses the fact that for each element a_i, the contribution to the final answer
can be computed using a geometric series and arithmetic progression formulas.
"""

n, k = map(int, input().split())
# Using formula: (k * k - 1) * sum(i * k**i for i in range(n)) // 6 % 998244353
print((k * k - 1) * sum(i * k**i for i in range(n)) // 6 % 998244353)


# https://github.com/VaHiX/CodeForces/