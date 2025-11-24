// Problem: CF 1282 B1 - K for the Price of One (Easy Version)
// https://codeforces.com/contest/1282/problem/B1

/*
 * Problem: B1. K for the Price of One (Easy Version)
 *
 * Algorithms/Techniques:
 *   - Greedy algorithm with sorting and two-pointer approach.
 *   - Sorting goods by price to facilitate optimal selection.
 *   - For each possible starting good (up to k), simulate buying as many
 *     pairs as possible using the offer rule where we pay for the most expensive
 *     item in a group of k items and get others free.
 *
 * Time Complexity: O(n log n + n * k) per test case, due to sorting and nested loop
 * Space Complexity: O(n), for storing prices and auxiliary vectors
 */

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, v, k;
    scanf("%lld %lld %lld", &n, &v, &k);
    std::vector<ll> a(n + 1, 0);  // Vector to store goods prices
    for (ll p = 1; p <= n; p++) {
      scanf("%lld", &a[p]);  // Read each price
    }
    sort(a.begin(), a.end());  // Sort prices in ascending order
    ll left(0), mx(0);  // left: coins spent so far, mx: max goods bought
    for (ll p = 0; p < k; p++) {  // Try starting from each of the first k elements
      left += a[p];  // Add current cheapest element to our spent amount
      if (v < left) {  // If not enough coins, break
        break;
      }
      ll tst = left;  // Temporary total cost for this combination
      ll idx(p);  // Index tracking which goods we've selected
      // While we can buy more groups of k items using the offer
      while ((idx + k <= n) && (tst + a[idx + k] <= v)) {
        idx += k;  // Move index by k to select next group
        tst += a[idx];  // Add cost of most expensive item in new group
      }
      // Check if we can take remaining item after last valid group
      if ((idx + k > n) && (tst + a[n] <= v)) {
        idx = n;  // Take the final item as a single purchase
      }
      mx = (idx > mx) ? idx : mx;  // Update maximum number of items taken
      if (mx >= n) {  // Early break optimization if all items can be bought
        break;
      }
    }
    printf("%lld\n", mx);  // Output the maximum number of goods
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/