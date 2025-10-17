// Problem: CF 1934 A - Too Min Too Max
// https://codeforces.com/contest/1934/problem/A

/*
 * Problem: A. Too Min Too Max
 * Algorithm: Finding maximum value of |a_i - a_j| + |a_j - a_k| + |a_k - a_l| + |a_l - a_i|
 *            for four distinct indices i, j, k, l in array a.
 *
 * Key Insight:
 * The expression can be simplified by considering the fact that the maximum occurs when
 * two elements are the minimum and two are the maximum (or vice versa) in the sorted order.
 * The result is 2 * (max_element + second_max - min_element - second_min).
 *
 * Time Complexity: O(n) per test case — one pass through array to find mins and maxes.
 * Space Complexity: O(1) — only using fixed extra variables regardless of input size.
 */

#include <cstdio>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long mna(1e7), mnb(1e7), mxa(-1e7), mxb(-1e7); // mna = min_a, mnb = second_min_a, mxa = max_a, mxb = second_max_a
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x <= mna) {
        mnb = mna;  // Update second min before updating min
        mna = x;
      } else if (x < mnb) {
        mnb = x;
      }
      if (x >= mxa) {
        mxb = mxa;  // Update second max before updating max
        mxa = x;
      } else if (x > mxb) {
        mxb = x;
      }
    }
    printf("%ld\n", 2 * (mxa + mxb - mna - mnb)); // Final result using key insight
  }
}


// https://github.com/VaHiX/codeForces/