# Problem: CF 925 A - Stairs and Elevators
# https://codeforces.com/contest/925/problem/A

"""
Algorithm: Stairs and Elevators
Purpose: Find minimum time to travel between two rooms in a hotel with stairs and elevators.
Techniques: Binary search with prefix/suffix optimization, greedy choice of nearby stairs/elevators.

Time Complexity: O(q * log(m) + q * log(n)) where q is number of queries, and m,n are dimensions.
Space Complexity: O(m + n) for storing stairs and elevators positions.

Approach:
- Preprocess stairs and elevators positions (already given as sorted arrays).
- For each query:
  - If same floor, direct path is optimal.
  - Otherwise:
    - Try all nearby stairs (at most 3) for potential shortest path via stairs.
    - Try all nearby elevators (at most 3) for potential shortest path via elevators.
    - Choose minimum time among all valid paths.

Key Operations:
- Binary search (bisect_left) to find closest stairs/elevators.
- Calculate time using: movement to point + elevator travel time + movement from point.
"""

import sys
from bisect import bisect_left
from math import ceil

input = sys.stdin.readline
n, m, cl, ce, v = map(int, input().split())
l = list(map(int, input().split()))  # stairs positions
e = list(map(int, input().split()))  # elevators positions
q = int(input())
for _ in range(q):
    x1, y1, x2, y2 = map(int, input().split())
    if x1 == x2:
        print(abs(y1 - y2))  # Direct horizontal movement
        continue
    ans = []
    idx = bisect_left(l, y1)  # Binary search for position of stair
    # Check 3 possible stairs (i-1, i, i+1) around the found position
    for i in range(idx - 1, idx + 2):
        if 0 <= i < cl:  # Ensure within bounds
            # Time = movement to stair + floor difference + movement from stair
            t = abs(y1 - l[i]) + abs(x1 - x2) + abs(l[i] - y2)
            ans.append(t)
    idx = bisect_left(e, y1)  # Binary search for position of elevator
    # Check 3 possible elevators (i-1, i, i+1) around the found position
    for i in range(idx - 1, idx + 2):
        if 0 <= i < ce:  # Ensure within bounds
            # Time = movement to elevator + elevator travel time + movement from elevator
            t = abs(y1 - e[i]) + ceil(abs(x1 - x2) / v) + abs(y2 - e[i])
            ans.append(t)
    print(min(ans))  # Output minimal time among all options


# https://github.com/VaHiX/CodeForces/