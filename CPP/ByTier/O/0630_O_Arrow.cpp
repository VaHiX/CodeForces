// Problem: CF 630 O - Arrow
// https://codeforces.com/contest/630/problem/O

/*
 * Purpose: This program computes the coordinates of an arrow shape composed of
 *          a triangle and a rectangle, based on a given point, direction vector,
 *          and dimensions. The arrow is oriented such that its tip points in the
 *          direction of the vector (vx, vy), and the coordinates are output in
 *          counter-clockwise order starting from the tip.
 *
 * Algorithm: 
 *   - Normalize the direction vector (vx, vy) to get unit vector components si (sin) and co (cos).
 *   - Use rotation matrix defined by si and co to rotate and translate the arrow points from
 *     a local coordinate system (centered at the base of the triangle) to the global coordinate
 *     system centered at (px, py).
 *   - The arrow consists of:
 *     - Triangle with base 'a' and height 'b'
 *     - Rectangle with width 'c' and height 'd'
 *   - The tip of the triangle is placed at (0, b) in local coordinates, and
 *     the base of the triangle is centered at (0, 0) in local coordinates, matching
 *     with the center of the rectangle's side of length 'c'.
 *   - The 7 points are generated in counter-clockwise order.

 * Time Complexity: O(1) - Fixed number of operations.
 * Space Complexity: O(1) - Only a constant amount of extra space is used.
 */
#include <cmath>
#include <cstdio>
#define pt(x, y)                                                               \
  printf("%.12f %.12f\n", x *co + y * si + px, -x * si + y * co + py);
int main() {
  int py, px, vx, vy, a, b, c, d;
  double si, co;
  scanf("%d%d%d%d%d%d%d%d", &px, &py, &vx, &vy, &a, &b, &c, &d);
  si = vx / hypot(vx, vy);  // Compute sin of angle from vector
  co = vy / hypot(vx, vy);  // Compute cos of angle from vector
  pt(0, b);                 // Tip of triangle (top of arrow)
  pt((-a / 2.0), 0);        // Left corner of triangle base
  pt((-c / 2.0), 0);        // Left corner of rectangle (same as triangle base)
  pt((-c / 2.0), (-d));     // Bottom-left corner of rectangle
  pt((c / 2.0), (-d));      // Bottom-right corner of rectangle
  pt((c / 2.0), 0);         // Right corner of rectangle (same as triangle base)
  pt((a / 2.0), 0);         // Right corner of triangle base
}


// https://github.com/VaHiX/CodeForces/