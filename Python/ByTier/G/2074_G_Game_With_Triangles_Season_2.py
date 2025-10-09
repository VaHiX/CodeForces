# Problem: CF 2074 G - Game With Triangles: Season 2
# https://codeforces.com/contest/2074/problem/G

"""
G. Game With Triangles: Season 2

Algorithms:
- Dynamic Programming with Interval Decomposition
- The problem is about selecting non-overlapping triangles from a polygon to maximize score
- Each triangle contributes a_score = a[i] * a[j] * a[k] where i < j < k are vertices in clockwise order
- Overlapping triangles are not allowed, which means that after choosing a triangle (i,j,k),
  the regions between these indices cannot be used again for other triangles

Time Complexity: O(n^3)
Space Complexity: O(n^2)

This solution uses dynamic programming where dp[l][r] represents the maximum score obtainable
from the subpolygon defined by vertices from index l to r (inclusive). The recurrence considers:
1. Removing one triangle in the middle and combining scores of left and right parts (non-overlapping)
2. Removing two triangles in a way that they do not overlap, using a specific configuration
"""

import sys


def max_triangle_score(n, a):
    dp = [[0] * (n + 1) for _ in range(n)]
    for k in range(3, n + 1):  # length of the interval [l, r)
        for l in range(n - k + 1):  # left index
            r = l + k  # right index (exclusive)
            cur = max(dp[l + 1][r], dp[l][r - 1])  # base cases: removing one end triangle
            for m in range(l + 1, r):  # middle vertex to form a triangle with l and r-1
                cur = max(cur, dp[l][m] + dp[m][r])  # split into two parts (no shared area)
                if m < r - 1:  # ensure there's space to make another triangle
                    # Add the triangle formed by l, m, r-1, with contribution a[l]*a[m]*a[r-1]
                    cur = max(cur, dp[l + 1][m] + dp[m + 1][r - 1] + a[l] * a[m] * a[r - 1])
            dp[l][r] = cur
    return dp[0][n]


t = int(sys.stdin.readline().strip())
results = []
for _ in range(t):
    n = int(sys.stdin.readline().strip())
    a = list(map(int, sys.stdin.readline().strip().split()))
    results.append(str(max_triangle_score(n, a)))
sys.stdout.write("\n".join(results) + "\n")


# https://github.com/VaHiX/codeForces/