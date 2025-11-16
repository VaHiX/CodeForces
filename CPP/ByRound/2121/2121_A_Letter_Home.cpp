// Problem: CF 2121 A - Letter Home
// https://codeforces.com/contest/2121/problem/A

/*
 * Problem: A. Letter Home
 * Purpose: Determine the minimum number of steps to visit all given positions
 *          starting from position 's' on the X-axis.
 *
 * Algorithm:
 *   - For each test case, compute the maximum distance to the left and right
 *     of the starting point 's' that needs to be covered.
 *   - The total minimum steps is the sum of max left distance and max right
 *     distance, but we subtract the overlap (minimum of the two) to avoid double counting.
 *
 * Time Complexity: O(n) per test case, where n is the number of positions.
 * Space Complexity: O(1), constant extra space (not counting input storage).
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, s;
    scanf("%ld %ld", &n, &s);
    long left(0), right(0);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x < s) {
        long u = s - x;
        left = (left > u ? left : u);  // Track maximum distance to the left of s
      } else {
        long u = x - s;
        right = (right > u ? right : u);  // Track maximum distance to the right of s
      }
    }
    long total = left + right + (left < right ? left : right);
    printf("%ld\n", total);
  }
}


// https://github.com/VaHiX/codeForces/