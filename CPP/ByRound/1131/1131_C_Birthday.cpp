// Problem: CF 1131 C - Birthday
// https://codeforces.com/contest/1131/problem/C

/*
 * Purpose: To arrange children in a circle such that the maximum difference 
 *          between the heights of two adjacent children is minimized.
 * 
 * Algorithm: 
 *   1. Sort the heights in ascending order.
 *   2. Place elements at even indices (0, 2, 4, ...) first.
 *   3. Then place elements at odd indices in reverse order (n-1, n-3, ...).
 * 
 * Time Complexity: O(n log n) due to sorting.
 * Space Complexity: O(n) for storing the heights.
 */

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  sort(a.begin(), a.end());  // Sort the heights in ascending order
  for (long p = 0; p < n; p += 2) {
    printf("%ld ", a[p]);  // Print elements at even indices first
  }
  for (long p = n - 1 - n % 2; p >= 1; p -= 2) {
    printf("%ld ", a[p]);  // Print elements at odd indices in reverse order
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/CodeForces/