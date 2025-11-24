// Problem: CF 1082 A - Vasya and Book
// https://codeforces.com/contest/1082/problem/A

/*
 * Problem: A. Vasya and Book
 * Purpose: Determine the minimum number of button presses needed to navigate from page x to page y,
 *          where each button press moves d pages forward or backward. If not possible, return -1.
 *
 * Algorithms/Techniques:
 * - Modular arithmetic to check reachability
 * - Greedy approach with case analysis
 *
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, x, y, d;
    scanf("%ld %ld %ld %ld", &n, &x, &y, &d);  // Read input values
    --n;  // Convert to 0-based indexing for calculations
    --x;  // Convert to 0-based indexing for calculations
    --y;  // Convert to 0-based indexing for calculations
    long res(-1);  // Initialize result to -1 (impossible case)
    long dist = y - x;  // Calculate direct distance between pages
    dist = (dist > 0) ? dist : -dist;  // Take absolute value of distance
    if (dist % d == 0) {
      // If direct path is possible (distance divisible by d)
      res = dist / d;
    } else if (n % d == 0 && y % d == 0) {
      // Special case: both end points are reachable via steps of size d
      long wa = y / d + (x + d - 1) / d;  // Cost to go from x to y via left side
      long wb = (n - x + d - 1) / d + (n - y) / d;  // Cost to go from x to y via right side
      res = wa < wb ? wa : wb;  // Choose minimum cost path
    } else if (y % d == 0) {
      // y is reachable, calculate steps needed from x
      res = y / d + (x + d - 1) / d;
    } else if ((n - y) % d == 0) {
      // y can be reached by moving to the end and then back in multiples of d
      res = (n - x + d - 1) / d + (n - y) / d;
    }
    printf("%ld\n", res);  // Output result for current test case
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/