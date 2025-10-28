// Problem: CF 1334 A - Level Statistics
// https://codeforces.com/contest/1334/problem/A

/*
 * Problem: Check if a sequence of level statistics (plays and clears) is valid.
 *
 * Algorithm: For each pair of consecutive statistics, verify that:
 *   1. Plays do not decrease (p_i >= p_{i-1})
 *   2. Clears do not decrease (c_i >= c_{i-1})
 *   3. The increase in clears cannot exceed the increase in plays
 *      (c_i - c_{i-1} <= p_i - p_{i-1})
 *
 * Time Complexity: O(n) per test case, where n is the number of moments.
 * Space Complexity: O(1), only using a few variables for tracking.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a(0), b(0); // Track previous plays and clears
    bool res(true);  // Flag to indicate if sequence is valid
    long n;
    scanf("%ld", &n);
    for (long p = 0; p < n; p++) {
      long x, y;
      scanf("%ld %ld", &x, &y);  // Read current plays and clears
      
      // Check if plays or clears decreased -> invalid
      if (x < a) {
        res = false;
      }
      if (y < b) {
        res = false;
      }
      
      // Check if clears increased more than plays -> invalid
      if (x - a < y - b) {
        res = false;
      }
      
      a = x;  // Update previous plays
      b = y;  // Update previous clears
    }
    puts(res ? "YES" : "NO");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/