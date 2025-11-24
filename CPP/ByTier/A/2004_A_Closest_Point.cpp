// Problem: CF 2004 A - Closest Point
// https://codeforces.com/contest/2004/problem/A

/*
 * Problem: Add a point to a set of points on a line such that the new point
 *          becomes the closest to every existing point in the set.
 *
 * Algorithm:
 *   - For each test case, we check if there exists a point x such that:
 *     1. x is not already in the set (integer constraint).
 *     2. x is closer to all points than any other point in the set.
 *   - This can be solved by checking for gaps between consecutive points.
 *     If there's an even gap (i.e., difference > 1), and it is the only gap,
 *     then we can place a new point exactly at the middle of that gap.
 *   
 * Time Complexity: O(n) per test case, where n is the number of points
 * Space Complexity: O(1), constant extra space
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long a, b;
    for (long p = 0; p < n; p++) {
      b = a;        // Store previous point
      scanf("%ld", &a);  // Read current point
    }
    // Check if the last gap between consecutive points is exactly 2
    // This means we can place a point at middle to be closest to both
    puts((n == 2 && (b - a > 1 || b - a < -1)) ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/