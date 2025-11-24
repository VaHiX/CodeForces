# Problem: CF 2119 B - Line Segments
# https://codeforces.com/contest/2119/problem/B

"""
B. Line Segments
Algorithm: Geometric validation using triangle inequality
Time Complexity: O(n) per test case, where n is the number of operations
Space Complexity: O(1), only using a few variables for computation

Approach:
- For each test case, calculate the direct Euclidean distance between start and end points.
- Then compute the minimum and maximum possible distances that can be achieved 
  after all moves, based on the given step lengths.
- The key insight is that the final position must be reachable within a range
  defined by the sum of all steps (maximal reach) and the difference between 
  the largest step and the rest (minimal reach).
- If the required distance lies within this valid range, then it's possible to reach,
  otherwise not.

The condition checked:
    max(0, 2 * max(a) - sum(a)) <= dis <= sum(a)
"""

from math import sqrt

t = int(input())
for tc in range(t):
    n = int(input())
    x0, y0, x1, y1 = map(int, input().split())
    a = list(map(int, input().split()))
    dis = sqrt(((x0 - x1) ** 2 + (y0 - y1) ** 2))
    if max(0, 2 * max(a) - sum(a)) <= dis <= sum(a):
        print("YES")
    else:
        print("NO")


# https://github.com/VaHiX/codeForces/