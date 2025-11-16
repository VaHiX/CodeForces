// Problem: CF 1114 A - Got Any Grapes?
// https://codeforces.com/contest/1114/problem/A

#include <cstdio>
/* 
 * Problem: A. Got Any Grapes?
 * 
 * Purpose: Determine if a given set of green, purple, and black grapes can be distributed among 
 *          Andrew, Dmitry, and Michal according to their preferences and required amounts.
 * 
 * Algorithm: Greedy distribution check.
 *   - Andrew needs at least x green grapes (only green grapes).
 *   - Dmitry needs at least y grapes, excluding black ones (can take green and purple).
 *   - Michal needs at least z grapes (any type).
 * 
 * The approach checks if we can satisfy all three conditions:
 *   1. Andrew's need for green grapes (x <= a)
 *   2. Dmitry's need for non-black grapes (x + y <= a + b), after allocating x to Andrew
 *   3. Michal's need for remaining grapes (x + y + z <= a + b + c), after allocating to Andrew and Dmitry
 * 
 * Time Complexity: O(1) - constant time operations
 * Space Complexity: O(1) - only a few variables used
 */
int main() {
  long x, y, z;
  scanf("%ld %ld %ld", &x, &y, &z);
  long a, b, c;
  scanf("%ld %ld %ld", &a, &b, &c);
  // Check if it is possible to distribute grapes according to constraints
  bool possible = (x <= a) && (x + y <= a + b) && (x + y + z <= a + b + c);
  puts(possible ? "YES" : "NO");
  return 0;
}


// https://github.com/VaHiX/CodeForces/