# Problem: CF 2114 D - Come a Little Closer
# https://codeforces.com/contest/2114/problem/D

"""
D. Come a Little Closer

Purpose:
This code solves a problem where we have n monsters placed on a large 10^9 x 10^9 grid. 
We can move one monster to an unoccupied cell once, and then select a rectangle that covers all monsters.
The goal is to minimize the total area of the rectangle needed.

Approach:
- Sort the x and y coordinates separately.
- Iterate over each monster's position to consider it as a potential "corner" of the final rectangle.
- For each such corner, calculate how much we can reduce the rectangle size by moving that monster,
  considering only those positions that are on the boundaries.
- If moving a monster reduces the area to n-1, compute the minimal possible cost.
- Time and Space Complexity:
    - Time: O(n log n) due to sorting
    - Space: O(n) for storing coordinates

Algorithm/Techniques:
- Coordinate compression
- Sorting
- Greedy strategy based on boundary handling

"""

import sys

t = int(sys.stdin.readline())
for _ in range(int(t)):
    n = int(sys.stdin.readline())
    li = []
    xi = []
    yi = []
    for _ in range(n):
        x, y = map(int, sys.stdin.readline().split())
        li.append((x, y))
        xi.append(x)
        yi.append(y)
    xi.sort()
    yi.sort()
    if n == 1:
        print(1)
        continue
    ans = 10**20
    for x, y in li:
        xdis = xi[-1] - xi[0] + 1  # width of the current bounding box
        ydis = yi[-1] - yi[0] + 1  # height of the current bounding box
        
        # If the monster is at left boundary, reduce width by the distance to next point
        if x == xi[0]:
            xdis -= xi[1] - xi[0]
        # If the monster is at right boundary, reduce width by the distance to previous point
        if x == xi[-1]:
            xdis -= xi[-1] - xi[-2]
        # If the monster is at bottom boundary, reduce height by the distance to next point
        if y == yi[0]:
            ydis -= yi[1] - yi[0]
        # If the monster is at top boundary, reduce height by the distance to previous point
        if y == yi[-1]:
            ydis -= yi[-1] - yi[-2]
        
        # If by moving one monster we can cover all but one (total n-1), check for minimal extra area
        if xdis * ydis == n - 1:
            ans = min(ans, min(xdis * (ydis + 1), (xdis + 1) * ydis))
        else:
            ans = min(ans, xdis * ydis)
    print(ans)


# https://github.com/VaHiX/codeForces/