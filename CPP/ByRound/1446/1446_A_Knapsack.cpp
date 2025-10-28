// Problem: CF 1446 A - Knapsack
// https://codeforces.com/contest/1446/problem/A

/*
 * Problem: Knapsack with constrained capacity
 * Purpose: Select a subset of items such that their total weight C satisfies
 *          ceil(W/2) <= C <= W. If multiple solutions exist, any one is acceptable.
 *
 * Algorithm:
 *   - Sort the items by weight (ascending).
 *   - Greedily add items until the cumulative weight exceeds W/2 and is at most W.
 *   - If an item causes the total to exceed W, we try resetting and starting fresh
 *     from that item, but only if the item itself is <= W.
 *
 * Time Complexity: O(n log n) due to sorting; overall process is linear.
 * Space Complexity: O(n) for storing items and results.
 */

#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, cap;
    scanf("%lld %lld", &n, &cap);
    std::vector<std::pair<ll, ll>> w(n); // Weight and original index
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &w[p].first);      // Read weight
      w[p].second = p + 1;             // Store original index (1-based)
    }
    sort(w.begin(), w.end());          // Sort by weight

    std::vector<ll> res;               // Result indices
    ll cs(0);                          // Current sum of weights
    for (ll p = 0; p < n; p++) {
      ll cur = w[p].first;             // Current item's weight
      ll which = w[p].second;          // Current item's original index
      ll tst = cs + cur;               // Tentative new sum

      if (2 * tst < cap) {
        // Still too small, include this item
        cs += cur;
        res.push_back(which);
      } else if (cap <= 2 * tst && tst <= cap) {
        // Within valid range [W/2, W], add and terminate
        cs += cur;
        res.push_back(which);
        break;
      } else if (cur <= cap) {
        // Current item is small enough to be a new start
        cs = cur;
        res = std::vector<ll>(1, which);
        break;
      } else {
        // Item too large, impossible solution from here
        res = std::vector<ll>(0);
        break;
      }
    }

    if (cap <= 2 * cs && cs <= cap && res.size() > 0) {
      // Valid solution found
      printf("%ld\n", res.size());
      for (long p = 0; p < res.size(); p++) {
        printf("%lld ", res[p]);
      };
      puts("");
    } else {
      puts("-1");
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/