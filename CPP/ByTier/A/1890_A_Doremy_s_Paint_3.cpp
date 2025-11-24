// Problem: CF 1890 A - Doremy's Paint 3
// https://codeforces.com/contest/1890/problem/A

/*
 * Problem: A. Doremy's Paint 3
 *
 * Purpose:
 *   Determine if an array of integers can be rearranged to form a "good" array,
 *   where all adjacent element sums are equal.
 *
 * Algorithm:
 *   - For a good array, there must be at most two distinct values.
 *   - If there are two distinct values, one must appear more than once and the other
 *     appears only once, or vice versa. The counts of these values must be within 1 of each other.
 *   - If there is one value, it's always good.
 *
 * Time Complexity:
 *   O(n) per test case due to single pass through the array for counting.
 *
 * Space Complexity:
 *   O(1) as only a constant number of variables are used.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    bool possible(true);
    long a;
    scanf("%ld", &a);
    long cnta(1), b(0), cntb(0);
    for (long p = 1; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x == a) {
        ++cnta;
      } else if (cntb == 0) {
        b = x;
        cntb = 1;
      } else if (x == b) {
        ++cntb;
      } else {
        possible = false; // Found third distinct element -> impossible
      }
    }
    if (cntb > 0) {
      if (cnta > cntb + 1) {
        possible = false; // Too many 'a's, cannot balance
      }
      if (cntb > cnta + 1) {
        possible = false; // Too many 'b's, cannot balance
      }
    }
    puts(possible ? "Yes" : "No");
  }
}


// https://github.com/VaHiX/codeForces/