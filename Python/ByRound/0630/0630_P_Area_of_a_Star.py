# Problem: CF 630 P - Area of a Star
# https://codeforces.com/contest/630/problem/P

"""
Star Area Calculation

Algorithm: 
This program calculates the area of a star figure with n corners (where n is a prime number ≥ 5) inscribed in a circle of radius r.
The star is constructed by connecting each point on the circle to the two maximally distant points, forming a star with n points.
The formula used is derived from geometric properties of the star and involves trigonometric functions.

Mathematical approach:
The formula is derived from the geometry of regular star polygons.
For a star with n points inscribed in a circle of radius r, the area can be computed using:
Area = n * r^2 * sin(π/n) * sin(π/(2n)) / sin(3π/(2n))

Time Complexity: O(1) - The computation involves a fixed number of trigonometric operations.
Space Complexity: O(1) - Only a constant amount of extra space is used.
"""

import math

n, r = map(int, input().split())
print(
    math.sin(math.pi / (2 * n))  # sin(π/(2n)) - part of the star's geometric calculation
    * math.sin(math.pi / n)      # sin(π/n) - part of the star's geometric calculation  
    / math.sin(3 * math.pi / (2 * n))  # sin(3π/(2n)) - denominator for the star's geometric calculation
    * n                          # multiply by n for the total star area
    * r                          # multiply by radius
    * r                          # multiply by radius again (r^2)
)


# https://github.com/VaHiX/CodeForces/