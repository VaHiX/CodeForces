# Problem: CF 630 O - Arrow
# https://codeforces.com/contest/630/problem/O

"""
Arrow Drawing Tool

This program calculates and outputs the coordinates of an arrow shape composed of a triangle and a rectangle,
based on a given point, direction vector, and dimensions.

Algorithm:
- The arrow is defined by:
  - A point (px, py) which is the center of the triangle base and one side of the rectangle.
  - A direction vector (vx, vy) indicating the direction of the arrow tip.
  - Parameters a, b, c, d:
    - a, b: triangle with base a and height b.
    - c, d: rectangle with sides c and d.
- The triangle is isosceles with:
  - Base of length a, centered at (px, py)
  - Height b, perpendicular to the base and pointing in the direction specified by (vx, vy)
- The rectangle shares the side of length c with the triangle's base.
- The algorithm computes all 7 vertices of the arrow in counter-clockwise order.

Time Complexity: O(1) - constant time operations
Space Complexity: O(1) - only a fixed number of variables are used
"""

px, py, vx, vy, a, b, c, d = map(int, input().split())
a = a / 2  # Half base of triangle
xl = vx / (vx**2 + vy**2) ** 0.5  # Unit vector x-component in direction of (vx, vy)
yl = vy / (vx**2 + vy**2) ** 0.5  # Unit vector y-component in direction of (vx, vy)


def sus(aa, bb):
    # Print the point (px + aa, py + bb) in the required format
    print(str(px + aa) + " " + str(py + bb))


# Tip of the triangle (pointing in direction of (vx, vy))
sus(xl * b, yl * b)
# Left corner of triangle base
sus(-yl * a, xl * a)
# Left corner of rectangle (on the base of triangle)
sus(-yl * c / 2, xl * c / 2)
# Bottom left corner of rectangle
sus(-yl * c / 2 - xl * d, xl * c / 2 - yl * d)
# Bottom right corner of rectangle
sus(yl * c / 2 - xl * d, -xl * c / 2 - yl * d)
# Right corner of rectangle (on the base of triangle)
sus(yl * c / 2, -xl * c / 2)
# Right corner of triangle base
sus(yl * a, -xl * a)


# https://github.com/VaHiX/CodeForces/