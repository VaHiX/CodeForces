// Problem: CF 1436 A - Reorder
// https://codeforces.com/contest/1436/problem/A

/*
 * Problem: Reorder Array to Match Sum Condition
 *
 * Purpose:
 * This program determines whether elements of an array can be reordered such that
 * a specific nested sum formula equals a given value m.
 *
 * Formula Analysis:
 * The formula is: sum over i from 1 to n of (sum over j from i to n of (a[j] / j))
 * This simplifies to: sum over j from 1 to n of (a[j] * (n - j + 1) / j)
 * So the result depends only on the total sum of array elements, not their order.
 *
 * Algorithm:
 * - For each test case, simply compute the sum of all array elements
 * - If this sum equals m, then YES; otherwise NO
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    long s(0);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      s += x;  // Accumulate the sum of all elements
    }
    puts(s == m ? "YES" : "NO");  // Check if total sum equals target
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/