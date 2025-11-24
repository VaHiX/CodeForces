# Problem: CF 993 A - Two Squares
# https://codeforces.com/contest/993/problem/A

"""
Algorithm: Check Intersection of Two Squares
Techniques: 
- Sorting and set operations to extract bounding coordinates
- Brute-force search in rotated square's space for overlap

Time Complexity: O(1) - since the number of vertices and operations are bounded (4 vertices each)
Space Complexity: O(1) - only a fixed amount of extra variables are used

The code determines if a square with sides parallel to axes intersects with another square rotated by 45 degrees.
It does this by:
1. Extracting min/max x and y coordinates of each square
2. Checking whether any point from the rotated square lies within the axis-aligned square
"""

import sys

input = sys.stdin.readline
w = list(map(int, input().split()))  # Coordinates of axis-aligned square
s = list(map(int, input().split()))  # Coordinates of rotated square

# Extract x and y coordinates of the axis-aligned square
a1 = sorted({w[0], w[2], w[4], w[6]})  # sorted x-coordinates
a2 = sorted({w[1], w[3], w[5], w[7]})  # sorted y-coordinates

# Extract x and y coordinates of the rotated square
b1 = sorted({s[0], s[2], s[4], s[6]})  # sorted x-coordinates
b2 = sorted({s[1], s[3], s[5], s[7]})  # sorted y-coordinates

ew = 0  # flag to indicate if intersection is found

# Iterate through possible points in rotated square's coordinate system
for i in range(b1[1] - b1[0] + 1):
    for j in range(b2[1] - i, b2[1] + i + 1):
        # Check if the point (b1[0]+i, j) is inside the axis-aligned square
        if ((a1[0] <= b1[0] + i <= a1[1]) or (a1[0] <= b1[2] - i <= a1[1])) and (
            a2[0] <= j <= a2[1]
        ):
            ew = 1
            break
    if ew == 1:
        break

print("YES" if ew == 1 else "NO")


# https://github.com/VaHiX/CodeForces/