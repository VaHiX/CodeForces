// Problem: CF 2085 B - Serval and Final MEX
// https://codeforces.com/contest/2085/problem/B

/*
 * Problem: B. Serval and Final MEX
 * Purpose: Given an array of non-negative integers, perform operations to reduce it to a single element equal to 0.
 *          Each operation replaces a subarray with its MEX (minimum excluded value).
 * Algorithms/Techniques:
 *   - Greedy strategy based on presence of zeros.
 *   - Uses MEX calculation on segments of the array.
 *
 * Time Complexity: O(n^2) in worst case due to nested operations and MEX computation for each subarray.
 * Space Complexity: O(1) additional space beyond input storage.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long first(0), last(0);
    for (long p = 1; p <= n; p++) {
      long x;
      scanf("%ld", &x);
      if (x) {
        continue; // Skip non-zero elements
      }
      if (!first) {
        first = p; // Record the position of first zero
      }
      last = p;  // Keep updating the last zero's position
    }
    if (!last) {
      // No zeros in array: directly compute MEX of entire array (should be 0)
      printf("1\n1 %ld\n", n);
    } else if (first == 1 && last == n) {
      // All elements are zeros: replace first two, then the rest, finally merge all
      printf("3\n3 %ld\n1 2\n1 2\n", n);
    } else if (last != n) {
      // Zero at the end not included; avoid that part in first operation
      printf("2\n1 %ld\n1 2\n", n - 1);
    } else if (first != 1) {
      // Zero at start not included; avoid it in first operation
      printf("2\n2 %ld\n1 2\n", n);
    }
  }
}


// https://github.com/VaHiX/codeForces/