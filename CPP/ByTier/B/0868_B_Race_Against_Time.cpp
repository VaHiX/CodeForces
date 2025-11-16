// Problem: CF 868 B - Race Against Time
// https://codeforces.com/contest/868/problem/B

/*
 * Problem: Race Against Time
 * Purpose: Determine if Misha can move from position t1 to t2 on a clock face
 *          without crossing any of the three clock hands (hour, minute, second).
 * Algorithm:
 *   1. Convert all time components to degrees for positioning on a clock face.
 *   2. Calculate positions of hour, minute, and second hands.
 *   3. Determine the angular range between t1 and t2 (considering both directions).
 *   4. Check whether all three hands lie within the same angular segment
 *      (either all inside or all outside the segment) to allow a valid path.
 *
 * Time Complexity: O(1) - Fixed number of operations.
 * Space Complexity: O(1) - Only a constant amount of extra space used.
 */

#include <cstdio>
int main() {
  double h, m, s, t1, t2;
  scanf("%lf %lf %lf %lf %lf", &h, &m, &s, &t1, &t2);
  double da = 6 * s;           // Second hand position in degrees
  if (da > 360) {
    da -= 360;                 // Normalize angle to [0, 360)
  }
  double db = 6 * (m + s / 60.0); // Minute hand position in degrees
  if (db > 360) {
    db -= 360;                 // Normalize angle to [0, 360)
  }
  double dc = 30 * (h + m / 60.0 + s / 3600.0); // Hour hand position in degrees
  if (dc > 360) {
    dc -= 360;                 // Normalize angle to [0, 360)
  }
  double u = 30 * t1;          // Starting position converted to degrees
  double v = 30 * t2;          // Target position converted to degrees
  if (v < u) {                 // Ensure u <= v for comparison
    double x = u;
    u = v;
    v = x;
  }
  bool possible(false);
  // Check if all hands lie inside the segment [u, v]
  if ((u < da && da < v) && (u < db && db < v) && (u < dc && dc < v)) {
    possible = true;
  }
  // Or check if all hands lie outside the segment [u, v]
  if ((!(u < da && da < v)) && (!(u < db && db < v)) && (!(u < dc && dc < v))) {
    possible = true;
  }
  puts(possible ? "YES" : "NO");
  return 0;
}


// https://github.com/VaHiX/CodeForces/