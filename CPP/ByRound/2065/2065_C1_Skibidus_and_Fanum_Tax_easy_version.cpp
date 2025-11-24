// Problem: CF 2065 C1 - Skibidus and Fanum Tax (easy version)
// https://codeforces.com/contest/2065/problem/C1

/*
 * C1. Skibidus and Fanum Tax (easy version)
 *
 * Purpose:
 *   Determines whether an array 'a' can be sorted in non-decreasing order by applying
 *   at most one operation per element, where the operation replaces a[i] with b[0] - a[i].
 *   Since m=1, we have only one value in b.
 *
 * Algorithms/Techniques:
 *   - Greedy approach: process elements from left to right.
 *   - For each element, decide whether to apply the operation (flip it) or not,
 *     based on maintaining non-decreasing order. Specifically, consider:
 *     1. If current value is <= previous and <= flipped value → pick min of both (or keep as is).
 *     2. If only current is <= previous → no flip.
 *     3. If only flipped is <= previous → flip it.
 *     4. Else → impossible to maintain order.
 *
 * Time Complexity:
 *   O(n) per test case, since we iterate through array once.
 *
 * Space Complexity:
 *   O(n), for storing the input vector 'a'.
 */

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    std::vector<long> a(n);
    for (size_t p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    long b;
    scanf("%ld", &b);
    bool res(true);
    // Initialize first element with minimum of itself and its flipped version
    a[0] = std::min(a[0], b - a[0]);
    for (size_t p = 1; res && p < n; p++) {
      // If previous is <= current AND previous is <= flipped current
      if (a[p - 1] <= a[p] && a[p - 1] <= b - a[p]) {
        // Choose the smaller of current or flipped current to maintain order
        a[p] = std::min(a[p], b - a[p]);
      } else if (a[p - 1] <= a[p]) {
        // Previous is <= current → no need to flip current
      } else if (a[p - 1] <= b - a[p]) {
        // Previous is <= flipped current → flip current
        a[p] = b - a[p];
      } else {
        // No valid way to keep increasing → impossible
        res = false;
      }
    }
    puts(res ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/