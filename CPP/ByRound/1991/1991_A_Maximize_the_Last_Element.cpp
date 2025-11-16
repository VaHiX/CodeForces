// Problem: CF 1991 A - Maximize the Last Element
// https://codeforces.com/contest/1991/problem/A

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long mx(-1);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (p % 2) {
        continue;
      }
      // Only consider elements at even indices (0, 2, 4, ...)
      // because in the optimal strategy, we always pick the maximum
      // among elements that will remain after all operations.
      mx = (mx > x ? mx : x);
    }
    printf("%ld\n", mx);
  }
}
/*
 * Problem: Maximize the Last Element
 *
 * Algorithm/Techniques:
 *   - Greedy approach
 *   - The key insight is that when we repeatedly remove two adjacent elements,
 *     we are essentially merging parts of the array. Since we can choose which
 *     pairs to merge, we want to maximize the final element. It turns out that
 *     the best strategy is to always pick the maximum among all elements at even indices.
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1)
 */

// https://github.com/VaHiX/codeForces/