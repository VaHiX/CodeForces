// Problem: CF 1631 A - Min Max Swap
// https://codeforces.com/contest/1631/problem/A

/*
 * Problem: Min Max Swap
 * Algorithm: Greedy approach to minimize the product of maximum elements of two arrays.
 * Approach:
 *   For each pair of elements at index i, we have two choices: keep a[i] and b[i], or swap them.
 *   We aim to find the minimum possible value of max(a) * max(b).
 *   To do this optimally, at each position, we compute the minimum possible values for max(a) and max(b)
 *   by considering swapping or not swapping elements at that position:
 *     - For a[i] and b[i], we calculate x = min(a[i], b[i]) and y = max(a[i], b[i]).
 *     - We update global mxa = max(mxa, x) and mxb = max(mxb, y).
 *   The final result is mxa * mxb.
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) per test case for storing arrays a and b
 */

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]); // Read array a
    }
    std::vector<long> b(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &b[p]); // Read array b
    }
    long mxa(-1), mxb(-1);
    for (long p = 0; p < n; p++) {
      long x = (a[p] < b[p]) ? a[p] : b[p];   // x is the smaller of a[p] and b[p]
      long y = (a[p] > b[p]) ? a[p] : b[p];   // y is the larger of a[p] and b[p]
      mxa = (mxa > x) ? mxa : x;              // Update max of min values
      mxb = (mxb > y) ? mxb : y;              // Update max of max values
    }
    printf("%ld\n", mxa * mxb); // Print the product
  }
}


// https://github.com/VaHiX/codeForces/