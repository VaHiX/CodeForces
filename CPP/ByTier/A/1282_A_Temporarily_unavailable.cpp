// Problem: CF 1282 A - Temporarily unavailable
// https://codeforces.com/contest/1282/problem/A

/*
 * Problem: Calculate the time Polycarp spends outside the mobile network coverage
 *          while traveling from point 'a' to 'b' at speed 1 unit/minute.
 *
 * Algorithm:
 * - For each test case, we determine the intersection of:
 *   (1) The segment [a, b] (Polycarp's path)
 *   (2) The interval [c - r, c + r] (coverage area of base station)
 * - Compute the length of the uncovered portion of the path.
 *
 * Time Complexity: O(t), where t is the number of test cases.
 * Space Complexity: O(1), only using constant extra space.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b, c, d;
    scanf("%ld %ld %ld %ld", &a, &b, &c, &d);
    if (a > b) {
      long x = a;
      a = b;
      b = x;
    }
    long l(c - d), r(c + d);  // Coverage interval [l, r]
    long avail(0);
    if (r <= a || b <= l) {
      // No overlap between path and coverage
      avail = 0;
    } else if (l <= a && b <= r) {
      // Path is fully within coverage
      avail = b - a;
    } else if (a <= l && r <= b) {
      // Coverage is fully within path
      avail = r - l;
    } else {
      // Partial overlap - compute intersection
      long m = (a > l) ? a : l;
      long M = (b < r) ? b : r;
      avail = M - m;
    }
    printf("%ld\n", (b - a) - avail);  // Uncovered time = total path - covered time
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/