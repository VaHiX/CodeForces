# Problem: CF 1859 D - Andrey and Escape from Capygrad
# https://codeforces.com/contest/1859/problem/D

"""
Algorithm: 
- For each portal, we are given a range [l_i, r_i] and a teleportation range [a_i, b_i].
- We want to find the maximum coordinate reachable from a starting point x_i by using the portals optimally.
- Strategy:
  1. For all portals, we can move from any point in [l_i, r_i] to any point in [a_i, b_i].
  2. To optimize, we will merge overlapping segments that allow teleporting to the same region.
  3. Then for each query x_i, we perform binary search on merged valid segments to find the best place to teleport.
  
Time Complexity:
- Sorting the portals: O(n log n)
- Merging segments: O(n)
- Processing queries: O(q * log n)
- Overall: O(n log n + q * log n)

Space Complexity:
- Storing merged segments: O(n)
- Storing queries: O(q)
- Overall: O(n + q)
"""

import bisect
import sys

input = sys.stdin.readline
for _ in range(int(input())):
    n = int(input())
    l = []
    for i in range(n):
        a, _, _, b = map(int, input().split())  # Extract a_i and b_i
        l.append((a, b))
    l.sort()
    l2 = []
    for i in l:
        # If current segment overlaps with previous one, merge them
        if len(l2) > 0 and l2[-1][1] >= i[0]:
            l2[-1] = (l2[-1][0], max(l2[-1][1], i[1]))
        else:
            l2.append(i)
    input()
    l1 = list(map(int, input().split()))  # Read query points
    for i in l1:
        # Binary search to find the rightmost segment where i is within [a, b]
        x = bisect.bisect_right(l2, (i, 10**9)) - 1
        if x == -1:
            # No valid segment, stay at current position
            print(i)
        else:
            # The maximum reachable point is the max of current position and end of the best segment
            print(max(i, l2[x][1]), end=" ")
    print()


# https://github.com/VaHiX/CodeForces/