// Problem: CF 908 C - New Year and Curling
// https://codeforces.com/contest/908/problem/C

/*
 * Problem: C. New Year and Curling
 * 
 * Algorithm/Technique: Geometry Simulation
 * 
 * Time Complexity: O(n^2), where n is the number of disks. For each disk, we may need to check all previously placed disks.
 * Space Complexity: O(n), to store the x and y coordinates of the disks.
 * 
 * Description:
 * We simulate the process of placing disks on a 2D plane. Each disk is dropped from a height (y = 1e100) and falls
 * until it touches the ground (y = 0) or another disk. The disks are placed in order, and we compute the final y-coordinate
 * for each disk's center based on collisions with previously placed disks.
 * 
 * Approach:
 * - For each disk, calculate the maximum possible y such that it doesn't intersect any previously placed disk.
 * - Two disks intersect if the distance between their centers is less than or equal to twice the radius.
 * - If they intersect, calculate the new y-coordinate as the top of the other disk plus the vertical distance
 *   to avoid intersection, using the Pythagorean theorem.
 * 
 * Input:
 *   - n: number of disks
 *   - r: radius of each disk
 *   - x coordinates of the disks
 * 
 * Output:
 *   - Final y-coordinates of all disks
 */

#include <cmath>
#include <cstdio>
#include <vector>
int main() {
  long n;
  double r;
  scanf("%ld %lf", &n, &r);
  std::vector<double> vx(n), vy(n);  // Store x and y coordinates of disks
  for (long p = 0; p < n; p++) {
    double x;
    scanf("%lf", &x);
    double y(r);  // Start with y = r (top of disk at y = 1e100)
    for (long q = 0; q < p; q++) {
      // If disks don't overlap horizontally, skip
      if (vx[q] + 2 * r < x || x + 2 * r < vx[q]) {
        continue;
      }
      // Calculate the y-coordinate on top of disk q such that this disk doesn't overlap
      double cy = vy[q] + sqrt(4 * r * r - (x - vx[q]) * (x - vx[q]));
      y = (y > cy) ? y : cy;  // Take maximum y to avoid collisions
    }
    vx[p] = x;
    vy[p] = y;
  }
  for (long p = 0; p < n; p++) {
    printf("%.8lf ", vy[p]);
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/CodeForces/