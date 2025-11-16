# Problem: CF 1972 D1 - Reverse Card (Easy Version)
# https://codeforces.com/contest/1972/problem/D1

"""
Algorithm: Reverse Card (Easy Version)
Techniques: Mathematical Optimization with GCD and Modular Arithmetic

Time Complexity: O(m)
Space Complexity: O(1)

The problem asks to count pairs (a, b) such that:
1 <= a <= n, 1 <= b <= m
and (a + b) % (b * gcd(a, b)) == 0

Key insight:
We can rewrite the condition as:
(a + b) % (b * gcd(a, b)) == 0
This means (a + b) is divisible by (b * gcd(a, b))

Let g = gcd(a, b), then a = g * a', b = g * b' where gcd(a', b') = 1.
So the condition becomes:
(g * a' + g * b') % (g * b' * g) == 0
Which simplifies to:
(g * (a' + b')) % (g^2 * b') == 0
Further:
(a' + b') % (g * b') == 0

This is true if and only if (a' + b') = k * g * b' for integer k >= 1.
This implies: a' = k * g * b' - b' = b' * (k * g - 1)

So we can iterate through all b' (from 1 to m) and for each b', we count how many valid a' we can have, 
which leads to a formula involving floor division.

Instead of going deep into mathematical derivation, the code observes:
For a fixed b, if (a + b) % (b * gcd(a,b)) == 0,
we iterate on b from 1 to m, and for each b, count the valid a's. 
This simplifies to a summation trick based on divisibility properties.

We compute:
- x = (n + i) // i^2, for i from 1 to m
Summing all these x's gives us the total count.
Subtracting 1 corrects for overcounting in the formula.
"""

import sys

input = lambda: sys.stdin.readline().strip()

for _ in range(int(input())):
    n, m = map(int, input().split())
    ans = 0
    for i in range(1, m + 1):
        x = (n + i) // (i * i)  # Compute contribution of current b=i
        ans += x
    ans -= 1  # Adjust for double counting in the formula
    print(ans)


# https://github.com/VaHiX/CodeForces/