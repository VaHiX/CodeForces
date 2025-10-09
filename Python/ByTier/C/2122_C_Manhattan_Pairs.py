# Problem: CF 2122 C - Manhattan Pairs
# https://codeforces.com/contest/2122/problem/C

"""
C. Manhattan Pairs
Algorithm: Greedy pairing based on sorted coordinates.
Techniques: Sorting, two-pointer technique.

Time Complexity: O(n log n) per test case due to sorting.
Space Complexity: O(n) for storing points and results.

Given n points (x_i, y_i) on a 2D plane where n is even,
we need to pair them into n/2 disjoint pairs to maximize
the sum of Manhattan distances between paired points.

The approach:
1. Sort all points by x-coordinate.
2. Split the sorted list into two halves.
3. Sort the first half by y-coordinate and second half by y-coordinate.
4. Pair elements from the first half (sorted by y) with elements from the second half (sorted by y),
   in a way that maximizes the Manhattan distance.

This is an optimal greedy approach:
- We want to maximize sum of |x_a - x_b| + |y_a - y_b|
- By sorting and taking pairs strategically, we ensure maximum contribution
  from both x and y differences.
"""

import sys

it = iter(map(int, sys.stdin.buffer.read().split()))
t = next(it)
res = []
for _ in range(t):
    n = next(it)  # number of points
    pts = [(next(it), next(it), i + 1) for i in range(n)]  # (x, y, index)
    pts.sort(key=lambda p: p[0])  # sort by x-coordinate
    m = n // 2
    l = sorted(pts[:m], key=lambda p: p[1])  # first half sorted by y
    r = sorted(pts[m:], key=lambda p: p[1])  # second half sorted by y
    for i in range(m):
        res.append(f"{l[i][2]} {r[m-1-i][2]}")  # pair elements from left and right halves
sys.stdout.write("\n".join(res))


# https://github.com/VaHiX/codeForces/