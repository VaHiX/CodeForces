// Problem: CF 1547 A - Shortest Path with Obstacle
// https://codeforces.com/contest/1547/problem/A

/*
 * Problem: Shortest Path with Obstacle on 2D Grid
 *
 * Algorithm/Techniques: Manhattan Distance with Obstacle Avoidance
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 *
 * Description:
 * Given three points A(xa,ya), B(xb,yb), and F(xf,yf) on a 2D grid,
 * find the shortest Manhattan distance from A to B avoiding point F.
 * The movement is restricted to four adjacent cells (up, down, left, right).
 *
 * Approach:
 * - Calculate Manhattan distance between A and B.
 * - Check if the forbidden point F lies on the direct path between A and B.
 *   If so, a detour of 2 units is required to avoid it.
 * - Special cases are considered when A and B share same x or y coordinate
 *   and F lies on the line segment connecting them.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld\n", &t);
  while (t--) {
    long xa, ya, xb, yb, xf, yf;
    scanf("%ld %ld\n", &xa, &ya);        // Read start point A
    scanf("%ld %ld\n", &xb, &yb);        // Read end point B
    scanf("%ld %ld\n", &xf, &yf);        // Read forbidden point F
    long dx = xa - xb;
    if (dx < 0) {
      dx = -dx;
    }
    long dy = ya - yb;
    if (dy < 0) {
      dy = -dy;
    }
    long res = dx + dy;                  // Manhattan distance without obstacle
    // Check if F is on the straight path from A to B horizontally
    if (ya == yb && ya == yf &&
        ((xa < xf && xf < xb) || (xb < xf && xf < xa))) {
      res += 2;                          // Add detour around obstacle
    } else if (xa == xb && xa == xf &&
               ((ya < yf && yf < yb) || (yb < yf && yf < ya))) {
      res += 2;                          // Add detour around obstacle
    }
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/