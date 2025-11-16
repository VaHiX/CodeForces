// Problem: CF 895 A - Pizza Separation
// https://codeforces.com/contest/895/problem/A

/*
 * Problem: Pizza Separation
 * Purpose: To divide a circular pizza (cut into n sectors) into two continuous parts such that the absolute difference of their total angles is minimized.
 * Algorithm: 
 *   - Use prefix sums to quickly compute the sum of any continuous subarray.
 *   - For every possible continuous subarray (representing one sector), calculate its sum and the sum of the remaining part.
 *   - Compute the absolute difference between these two sums and keep track of the minimum.
 * 
 * Time Complexity: O(n^2)
 * Space Complexity: O(n)
 */
#include <cstdio>
#include <vector>
int main() {
  const long R = 360; // Total angle of the pizza
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n + 1, 0), b(n + 1, 0); // a stores input, b stores prefix sums
  long minDiff(R); // Initialize with maximum possible difference
  for (long p = 1; p <= n; p++) {
    scanf("%ld", &a[p]);
    b[p] = b[p - 1] + a[p]; // Build prefix sum array
  }
  for (long u = 1; u <= n; u++) {
    for (long v = 1; v <= u; v++) {
      long total = b[u] - b[v - 1]; // Sum of sector from v to u
      long diff = total - (R - total); // Difference between this sector and the rest
      if (diff < 0) {
        diff = -diff; // Take absolute value
      }
      minDiff = (minDiff < diff) ? minDiff : diff; // Update minimum difference
    }
  }
  printf("%ld\n", minDiff);
  return 0;
}


// https://github.com/VaHiX/CodeForces/