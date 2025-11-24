// Problem: CF 1485 A - Add and Divide
// https://codeforces.com/contest/1485/problem/A

/*
 * Problem: A. Add and Divide
 * Algorithms/Techniques: Simulation with optimization, iterating over possible values of b.
 * Time Complexity: O(100 * log_a(b)) per test case, which is effectively O(log a) since the loop runs up to 100 iterations.
 * Space Complexity: O(1) - only using a constant amount of extra space.
 *
 * Description:
 * Given two positive integers a and b, we can perform two operations:
 * 1. Replace a with floor(a / b)
 * 2. Increase b by 1
 *
 * Goal: Find the minimum number of operations to make a = 0.
 *
 * Approach:
 * For each test case:
 * - We start with initial a and b values.
 * - We calculate an initial result as (1 + a / b) which represents one operation of dividing a by b.
 * - Then we iterate for b values from b to b+100:
 *   - Skip the case when p == 1 because division by 1 has no effect.
 *   - Compute how many times we divide a by p until it becomes 0 using a while loop (number of divisions = div).
 *   - The total operations needed for this b value is (p - b) + div.
 *   - Keep the minimum among all computed values.
 * - Output the result.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b;
    scanf("%ld %ld", &a, &b);
    long res(1 + a / b); // Initial estimate: one division and possibly additional increments
    for (long p = b; p <= b + 100; p++) {
      if (p == 1) {
        continue; // Skip division by 1 as it's not useful
      }
      long div(0), cur(a);
      while (cur) {
        cur /= p; // Count how many times we divide a by p to get to 0
        ++div;
      }
      long cnt = (p - b) + div; // Operations: incrementing b from original b to p, plus divisions
      res = (res < cnt) ? res : cnt; // Keep the minimum
    }
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/