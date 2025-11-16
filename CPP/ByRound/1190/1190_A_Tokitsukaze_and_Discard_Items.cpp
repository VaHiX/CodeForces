// Problem: CF 1190 A - Tokitsukaze and Discard Items
// https://codeforces.com/contest/1190/problem/A

/*
 * Problem: A. Tokitsukaze and Discard Items
 * Algorithm/Techniques: Greedy, Simulation with Paging
 *
 * Time Complexity: O(m), where m is the number of special items
 * Space Complexity: O(m), for storing the positions of special items
 *
 * Description:
 * Tokitsukaze discards special items from a list of n items arranged in pages of k positions.
 * Each operation removes all special items on the first page containing at least one special item,
 * and then shifts items forward, repeating until no more items to discard.
 * We simulate this by grouping items into pages and tracking how many operations are needed.
 */

#include <cstdio>
#include <vector>
typedef long long ll;

int main() {
  ll n, m, k;
  scanf("%lld %lld %lld", &n, &m, &k);
  std::vector<ll> v(m + 1); // Store special item positions (1-indexed)
  for (int p = 1; p <= m; p++) {
    scanf("%lld", &v[p]);
  }
  ll ans(0), sum(0), now(1); // ans: total operations, sum: items moved/removed, now: current position in v
  while (now <= m) {
    // Calculate rightmost position of the page that contains v[now]
    ll r = ((v[now] - sum - 1) / k + 1) * k + sum;
    // While there are special items in this page, move them and increment count
    while (now <= m && v[now] <= r) {
      sum++; // Move item to the next position (simulate shifting)
      now++; // Process next special item
    }
    ans++; // One operation completed (discarding a full page's special items)
  }
  printf("%lld\n", ans);
  return 0;
}


// https://github.com/VaHiX/codeForces/