# Problem: CF 1458 A - Row GCD
# https://codeforces.com/contest/1458/problem/A

"""
Algorithm: Row GCD
Techniques: Mathematical GCD properties, prefix processing

Time Complexity: O(n log(max(a_i)) + m log(max(b_j)))
Space Complexity: O(n + m)

This solution uses the property that gcd(a_1 + b_j, a_2 + b_j, ..., a_n + b_j) 
is equal to gcd of differences and the minimum value in the first array plus b_j.
We compute the GCD of all differences (a_i - min(a)) and then for each b_j,
we calculate gcd of this GCD and (min(a) + b_j).
"""

import sys

input = sys.stdin.buffer.readline
a, b = map(int, input().split())
import math

c = list(map(int, input().split()))
d = list(map(int, input().split()))
s = max(c)
c = [s - i for i in c]  # Transform to differences from maximum
h = 0
for i in c:
    h = math.gcd(h, i)  # Compute GCD of all differences
for i in d:
    print(math.gcd(h, s + i), end=" ")  # For each b_j, compute final GCD


# https://github.com/VaHiX/codeForces/