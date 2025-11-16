# Problem: CF 1967 B1 - Reverse Card (Easy Version)
# https://codeforces.com/contest/1967/problem/B1

"""
Algorithm: Mathematical Analysis + Iteration
Time Complexity: O(m * log(m)) in worst case, but optimized due to early break
Space Complexity: O(1)

The problem asks to count pairs (a, b) such that:
1 <= a <= n, 1 <= b <= m
and (a + b) is divisible by b * gcd(a, b)

Key Insight:
Let g = gcd(a, b), so a = g * a', b = g * b' where gcd(a', b') = 1.
Then the condition becomes:
(a' * g + b' * g) % (b' * g * g) == 0
=> g * (a' + b') % (g * b' * g) == 0
=> (a' + b') % (b' * g) == 0

This means (a' + b') must be divisible by b' * g.
If b' * g divides (a' + b'), then let (a' + b') = k * b' * g for some integer k.
This implies a' = k * b' * g - b' = b' * (k * g - 1).

Also since gcd(a', b') = 1, we have a' and b' coprime.
We iterate over b' from 2 to m and for each b', compute how many valid values of a' exist.

The given optimized code uses a mathematical approach in a nested loop to count valid combinations efficiently.

It iterates through values of b starting from 2 to m, calculates a term k = i*i - i,
and calculates how many valid a values exist for each b, using integer division.
Finally, it adds n to account for cases where b = 1.
"""

import sys

input = sys.stdin.readline

t = int(input())
for tests in range(t):
    n, m = map(int, input().split())

    ANS = 0

    for i in range(2, m + 1):
        k = i * i - i
        if n < k:
            break
        ANS += (n - k) // (i * i) + 1

    print(ANS + n)


# https://github.com/VaHiX/CodeForces/