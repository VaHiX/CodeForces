// Problem: CF 1428 A - Box is Pull
// https://codeforces.com/contest/1428/problem/A

/*
 * Problem: Minimum Time to Move a Box in Coordinate Plane
 * 
 * Description:
 * Wabbit moves a box from point (x1, y1) to (x2, y2) on a coordinate plane.
 * He can only pull the box if he stands exactly 1 unit away along an axis.
 * Pulling moves the box 1 unit in the direction of pull and moves Wabbit 1 unit
 * in the same direction after pulling.
 * Moving without pulling allows free movement 1 unit per second in any of the 4 directions.
 * 
 * Algorithm:
 * The minimal time is determined by Manhattan distance plus additional steps
 * needed for pulling when both x and y distances are positive (i.e., when box moves diagonally).
 * 
 * Time Complexity: O(t) where t is number of test cases
 * Space Complexity: O(1)
 */
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long x1, y1, x2, y2;
    scanf("%ld %ld %ld %ld", &x1, &y1, &x2, &y2);
    long xd = x2 - x1;
    xd = (xd > 0) ? xd : -xd; // absolute difference in x-coordinates
    long yd = y2 - y1;
    yd = (yd > 0) ? yd : -yd; // absolute difference in y-coordinates
    long ans = xd + yd + 2 * (xd > 0 && yd > 0); // Manhattan distance + extra steps for diagonal movement
    printf("%ld\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/