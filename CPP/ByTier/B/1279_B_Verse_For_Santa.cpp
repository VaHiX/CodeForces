// Problem: CF 1279 B - Verse For Santa
// https://codeforces.com/contest/1279/problem/B

/*
 * Problem: B. Verse For Santa
 * Purpose: Determine which part to skip to maximize the number of presents
 *          under time constraint s, allowing at most one skip.
 * Algorithm: Greedy approach with prefix sums and tracking maximum element.
 *            - Iterate through parts accumulating time.
 *            - Track the maximum element seen so far and its position.
 *            - When total exceeds s, we must skip some part; best is to skip
 *              the largest element encountered so far.
 *            - If total never exceeds s, no need to skip (return 0).
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for storing the array
 */

#include <cstdio>
#include <vector>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, s;
    scanf("%lld %lld", &n, &s);
    std::vector<ll> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%lld", &a[p]);
    }
    ll d(0), mx(0), pos(0);
    for (ll p = 0; p < n; p++) {
      d += a[p];                    // Accumulate time
      if (a[p] > mx) {              // Update max element and its index
        mx = a[p];
        pos = p + 1;
      }
      if (d > s) {                  // If we exceed time limit, stop here
        break;
      }
    }
    printf("%lld\n", pos * (d > s));  // Print position if exceeded s, else 0
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/