// Problem: CF 1369 A - FashionabLee
// https://codeforces.com/contest/1369/problem/A

/*
 * Problem: FashionabLee
 * Algorithms/Techniques: Mathematical observation
 * Time Complexity: O(t), where t is the number of test cases
 * Space Complexity: O(1)
 *
 * A regular n-sided polygon is beautiful if it can be rotated such that
 * at least one edge is parallel to the X-axis and one edge is parallel to the Y-axis.
 * This happens when the polygon has a rotational symmetry of 90 degrees,
 * which occurs if and only if n is divisible by 4.
 *
 * For example:
 * - Triangle (n=3): Not beautiful
 * - Square (n=4): Beautiful
 * - 12-gon: Beautiful (12 % 4 == 0)
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    puts(n % 4 ? "NO" : "YES"); // If n is not divisible by 4, output NO; otherwise YES
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/