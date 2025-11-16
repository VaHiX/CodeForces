# Problem: CF 1999 E - Triple Operations
# https://codeforces.com/contest/1999/problem/E

"""
E. Triple Operations

Purpose:
This problem computes the minimum number of operations required to reduce all integers 
from l to r (inclusive) on a board down to 0 using specific operations:
- Pick two numbers x and y.
- Replace them with 3*x and floor(y/3).
Each number's "depth" or number of operations needed to reach 0 is determined by how many times
we can divide it by 3 before reaching 0. The final result for a range [l, r] comes from:
t[r] + t[l] - 2 * t[l-1], where t[i] represents the "depth" of number i.

Algorithms/Techniques:
Preprocessing using dynamic programming to compute depth of numbers.
The recurrence: t[i] = t[i // 3] + 1 for all i from 1 to M.
Then we accumulate prefix sums in-place.
Time Complexity: O(M) preprocessing, O(1) per query
Space Complexity: O(M)
"""

import sys

R = sys.stdin.readline
S = lambda: map(int, R().split())
P = print
M = 200000
t = [0] * (M + 1)

# Precompute the "depth" of each number using recurrence:
# t[i] = t[i // 3] + 1 (number of divisions by 3 to reach 0)
for i in range(1, M + 1):
    t[i] = t[i // 3] + 1

# Prefix sum: accumulate total operations up to index i
for i in range(M):
    t[i + 1] += t[i]

# Process queries
for _ in range(int(R())):
    l, r = S()
    # The formula computes the total number of operations
    # needed over the range [l, r]
    P(t[r] + t[l] - 2 * t[l - 1])


# https://github.com/VaHiX/codeForces/