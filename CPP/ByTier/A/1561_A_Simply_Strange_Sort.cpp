// Problem: CF 1561 A - Simply Strange Sort
// https://codeforces.com/contest/1561/problem/A

/*
 * Problem: A. Simply Strange Sort
 * Purpose: Simulates a sorting algorithm on a permutation where in each iteration,
 *          adjacent elements at odd/even indices are swapped if they're out of order.
 *          The goal is to find the number of iterations needed to sort the array.
 *
 * Algorithm:
 *   - Use a helper function `sorted()` to check if array is sorted
 *   - In main loop, simulate iterations:
 *     * Odd iteration: process pairs (1,3), (5,7), ... (odd indices)
 *     * Even iteration: process pairs (2,4), (6,8), ... (even indices)
 *   - Count iterations until sorted
 *
 * Time Complexity: O(n^2) in worst case - each element may need to be moved O(n) times,
 *                  and we might need up to O(n) iterations.
 * Space Complexity: O(n) for the vector storage of the permutation.
 */

#include <cstdio>
#include <vector>
bool sorted(const std::vector<long> &v) {
  for (long p = 1; p < v.size(); p++) { // Check if array is sorted
    if (v[p - 1] > v[p]) {
      return false;
    }
  }
  return true;
}
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]); // Read the permutation
    }
    long cnt(0); // Initialize iteration counter
    while (!sorted(a)) { // Continue until sorted
      // Determine starting index based on parity of iterations
      for (long p = (cnt % 2); p + 1 < n; p += 2) {
        if (a[p] > a[p + 1]) { // Swap if out of order
          long x = a[p];
          a[p] = a[p + 1];
          a[p + 1] = x;
        }
      }
      ++cnt; // Increment iteration count
    }
    printf("%ld\n", cnt); // Print result for this test case
  }
}


// https://github.com/VaHiX/codeForces/