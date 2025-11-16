# Problem: CF 1589 A - Mathematical Addition
# https://codeforces.com/contest/1589/problem/A

"""
Mathematical Addition

This problem requires finding integers x and y such that the equation:
    x/u + y/v = (x+y)/(u+v)
is satisfied, with the constraint that (x, y) ≠ (0, 0).

Algebraic manipulation of the equation leads to:
    x(u + v) / u + y(u + v) / v = x + y
    (x + y)(1/u + 1/v) = (x + y)/(u + v)
    (x + y)(1/u + 1/v - 1/(u + v)) = 0

From this derivation, if x + y = 0, i.e., y = -x, we obtain:
    x/u - x/v = 0
    x(1/u - 1/v) = 0

For non-zero x, this means 1/u = 1/v, which implies u = v.
So a general approach is to choose x = -u^2 and y = v^2.

Time Complexity: O(1)
Space Complexity: O(1)
"""

from sys import stdin

for _ in range(int(input())):
    u, v = map(int, stdin.readline().split())
    print(-(u**2), v**2)


# https://github.com/VaHiX/CodeForces/