# Problem: CF 1841 D - Pairs of Segments
# https://codeforces.com/contest/1841/problem/D

"""
Algorithm: Greedy approach to maximize pairwise intersections
Time Complexity: O(n log n) due to sorting
Space Complexity: O(1) excluding input storage

The problem asks us to find the minimum number of elements to remove from an array of segments 
so that the remaining segments can be paired such that each pair intersects, and no two pairs 
intersect with each other.

This is solved greedily:
1. Sort segments by their right endpoint.
2. For each segment:
   - If it intersects with the last selected segment (using a greedy rule), skip it.
   - Otherwise, if we have a pending segment (`cur`), pair them and increment answer.
   - Else, store this segment as pending.

The number of pairs we can form is `ans`, so the number of elements to remove is `n - 2 * ans`.
"""

import sys

input = sys.stdin.readline

t = int(input())

for _ in range(t):
    n = int(input())
    points = [list(map(int, input().split())) for _ in range(n)]
    points.sort(key=lambda x: x[1])  # Sort by right endpoint

    R = -1  # Last right endpoint of a selected pair
    cur = 0  # Right endpoint of current pending segment
    ans = 0  # Number of pairs we can form

    for x, y in points:
        if x <= R:
            # Current segment intersects with the last selected pair, skip it
            continue
        if cur and x <= cur:
            # Current segment intersects with the pending segment, form a pair
            ans += 1
            cur = 0  # Reset pending
            R = y    # Update last selected right endpoint
        else:
            # No intersection with pending segment, set current as pending
            cur = y

    print(n - 2 * ans)  # Minimum elements to remove = total - 2 * number of pairs


# https://github.com/VaHiX/CodeForces/