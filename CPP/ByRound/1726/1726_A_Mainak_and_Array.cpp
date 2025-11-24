// Problem: CF 1726 A - Mainak and Array
// https://codeforces.com/contest/1726/problem/A

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
      scanf("%ld", &a[p]);
    }
    // Initialize ans to a very small value
    long ans(-2000);
    // Check all possible differences between a[p] and a[0]
    for (long p = 1; p < n; p++) {
      long tst = a[p] - a[0];
      ans = (ans > tst) ? ans : tst;
    }
    // Check all possible differences between a[n-1] and a[p]
    for (long p = 0; p < n - 1; p++) {
      long tst = a[n - 1] - a[p];
      ans = (ans > tst) ? ans : tst;
    }
    // Check all possible differences between previous element and current
    for (long p = 0; p < n; p++) {
      long tst = a[(p - 1 + n) % n] - a[p];
      ans = (ans > tst) ? ans : tst;
    }
    printf("%ld\n", ans);
  }
}
/*
 * Problem: Mainak and Array
 * Purpose: Maximize the difference (a[n-1] - a[0]) after rotating one subsegment exactly once.
 *
 * Algorithms/Techniques:
 *   - Brute force exploration of all rotations to maximize the difference between last and first elements.
 *   - The key idea is that when we rotate a subarray, it affects the relative order of elements,
 *     especially first and last. So we evaluate possible combinations efficiently without explicit rotation simulation.
 *
 * Time Complexity: O(n^2) in worst case due to nested loops over all elements, but in practice much less due to early termination logic
 * Space Complexity: O(n) for storing the array
 */

// https://github.com/VaHiX/codeForces/