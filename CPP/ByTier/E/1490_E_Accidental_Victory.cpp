// Problem: CF 1490 E - Accidental Victory
// https://codeforces.com/contest/1490/problem/E

/*
 * Problem: E. Accidental Victory
 * Purpose: Determine which players have a non-zero probability of winning
 *          in a token-based elimination tournament.
 *
 * Algorithm:
 *   - Sort players by token count (ascending).
 *   - Compute prefix sums of token counts.
 *   - Find the first index where cumulative sum is at least the next player's tokens.
 *   - All players from that index onward can potentially win.
 *   - Output those players in increasing order.
 *
 * Time Complexity: O(n log n) per test case due to sorting
 * Space Complexity: O(n) for storing vectors and prefix sums
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
    ll n;
    scanf("%lld", &n);
    std::vector<std::pair<ll, ll>> v(n); // Store {tokens, original_index}
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &v[p].first);
      v[p].second = p + 1; // Store original index (1-based)
    }
    sort(v.begin(), v.end()); // Sort by tokens (ascending)

    std::vector<ll> cs(n, 0); // Prefix sums of tokens
    cs[0] = v[0].first;
    for (ll p = 1; p < n; p++) {
      cs[p] = cs[p - 1] + v[p].first; // Compute prefix sum
    }

    ll first(n - 1); // Initialize to last index
    for (ll p = n - 2; p >= 0; p--) {
      if (cs[p] >= v[p + 1].first) {
        first = p; // Found the first valid position
      } else {
        break; // Stop when condition fails
      }
    }

    std::vector<ll> w; // Collection of possible winners
    for (ll p = first; p < n; p++) {
      w.push_back(v[p].second); // Add original index to result
    }
    sort(w.begin(), w.end()); // Sort final answer by original index

    printf("%ld\n", w.size());
    for (ll p = 0; p < w.size(); p++) {
      printf("%lld ", w[p]);
    }
    puts(""); // Newline after each case
  }
}


// https://github.com/VaHiX/codeForces/