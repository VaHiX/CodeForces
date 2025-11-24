// Problem: CF 2051 B - Journey
// https://codeforces.com/contest/2051/problem/B

/*
 * Problem: B. Journey
 * Purpose: Determine the day on which Monocarp completes his hiking journey,
 *          where the walking pattern repeats every 3 days (a, b, c).
 *
 * Algorithm:
 * - The pattern a, b, c repeats cyclically.
 * - For each test case:
 *   1. Calculate how many complete cycles of (a + b + c) fit into n.
 *   2. Use modulo to find remaining distance after full cycles.
 *   3. Determine which day the remaining distance falls on.
 *
 * Time Complexity: O(1) - constant time operations
 * Space Complexity: O(1) - only using a few variables
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, a, b, c;
    scanf("%ld %ld %ld %ld", &n, &a, &b, &c);
    long s(a + b + c);        // Total distance in one cycle (a + b + c)
    long t = 3 * (n / s);     // Number of days from complete cycles (3 days per cycle)
    n %= s;                   // Remaining distance after full cycles

    // Determine the day based on remaining distance
    if (0 < n && n <= a) {
      ++t;                    // First day of new cycle
    } else if (a < n && n <= a + b) {
      t += 2;                 // Second day of new cycle
    } else if (n > a + b) {
      t += 3;                 // Third day of new cycle
    }

    printf("%ld\n", t);
  }
}


// https://github.com/VaHiX/codeForces/