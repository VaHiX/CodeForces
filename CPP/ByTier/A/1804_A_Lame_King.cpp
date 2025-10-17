// Problem: CF 1804 A - Lame King
// https://codeforces.com/contest/1804/problem/A

/*
 * Problem: A. Lame King
 * Algorithm: Math-based approach to compute minimum time for a lame king to reach a target position on a 201x201 board.
 *
 * Key Observations:
 * - The king starts at (0, 0) and wants to reach (a, b).
 * - King has 5 possible moves per second: skip, up, down, left, right.
 * - Cannot repeat the same move in two consecutive seconds.
 * - Optimal strategy is based on Manhattan distances and greedy move selection while respecting move restrictions.
 *
 * Approach:
 * - Calculate absolute values of x and y to work with non-negative coordinates.
 * - Ensure x <= y (swap if necessary) so that we process the smaller distance first.
 * - The minimum time is computed as 2*y - (y > x), which accounts for optimal alternating moves and restrictions.
 *
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long x, y;
    scanf("%ld %ld", &x, &y);
    x = (x < 0) ? -x : x;   // Take absolute value of x
    y = (y < 0) ? -y : y;   // Take absolute value of y
    if (x > y) {
      long z = x;
      x = y;
      y = z;                // Ensure x is the smaller coordinate
    }
    printf("%ld\n", 2 * y - (y > x));  // Compute and print result
  }
}


// https://github.com/VaHiX/codeForces/