// Problem: CF 935 C - Fifa and Fafa
// https://codeforces.com/contest/935/problem/C

/*
 * Problem: Fifa and Fafa
 * Purpose: Find the optimal position and radius of a Wi-Fi access point inside a circular flat,
 *          such that the uncovered area is minimized, and the access point does not allow
 *          access to points outside the flat or to Fafa's laptop.
 *
 * Algorithm:
 * - The flat is a circle centered at (x1, y1) with radius R.
 * - Fafa's laptop is at (x2, y2).
 * - The access point must be inside the flat (within radius R from center).
 * - We aim to minimize the uncovered area inside the flat.
 * - We consider two cases:
 *   1. If the distance from flat center to Fafa's laptop (d1) is greater than or equal to R:
 *      The best position for the access point is at the flat center (x1, y1) with radius R.
 *   2. Otherwise:
 *      We compute two candidate points on the line from (x1, y1) to (x2, y2), at distance r
 *      from (x2, y2). The one closer to the flat center gives the optimal solution.
 *
 * Time Complexity: O(1) - constant time operations.
 * Space Complexity: O(1) - only a constant amount of variables are used.
 */

#include <cmath>
#include <cstdio>

// Function to calculate Euclidean distance between two points
double getDist(double x1, double y1, double x2, double y2) {
  return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

int main() {
  double R, x1, y1, x2, y2;
  scanf("%lf %lf %lf %lf %lf", &R, &x1, &y1, &x2, &y2);
  
  double d1 = getDist(x1, y1, x2, y2);  // Distance from flat center to Fafa's laptop
  
  double r = 0.5 * (d1 + R);  // Initial radius for access point
  
  double xa, ya, xb, yb;  // Two candidate positions for the access point
  
  if (d1 >= R) {
    // If Fafa is outside or on the border of the flat, put access point at flat center
    xa = xb = x1;
    ya = yb = y1;
    r = R;
  } else if (x1 != x2) {
    // If Fafa is inside the flat and not vertically aligned, compute two possible points
    double tan = (y2 - y1) / (x2 - x1);  // Slope of the line from flat center to Fafa
    xa = x2 + r / sqrt(tan * tan + 1);   // Point to the right
    xb = x2 - r / sqrt(tan * tan + 1);   // Point to the left
    ya = y2 + tan * r / sqrt(tan * tan + 1);  // Corresponding y-coordinate
    yb = y2 - tan * r / sqrt(tan * tan + 1);  // Corresponding y-coordinate
  } else {
    // If Fafa is directly above or below flat center, handle vertical case
    xa = xb = x2;
    ya = y2 - r;
    yb = y2 + r;
  }
  
  // Calculate distances from flat center to both potential access point locations
  double dista = getDist(x1, y1, xa, ya);
  double distb = getDist(x1, y1, xb, yb);
  
  // Output the point which brings the access point closer to the center
  // (and thus minimizes the uncovered area)
  if (dista < distb) {
    printf("%.9lf %.9lf %.9lf\n", xa, ya, r);
  } else {
    printf("%.9lf %.9lf %.9lf\n", xb, yb, r);
  }
  
  return 0;
}


// https://github.com/VaHiX/CodeForces/