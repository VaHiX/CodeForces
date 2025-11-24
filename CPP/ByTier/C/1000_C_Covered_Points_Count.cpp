// Problem: CF 1000 C - Covered Points Count
// https://codeforces.com/contest/1000/problem/C

/*
C. Covered Points Count
Algorithm: Coordinate compression with sweep line technique
Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for storing events and result vector

The solution uses a sweep line algorithm to count how many points are covered by exactly k segments for each k in [1..n].
It creates events for segment starts and ends, sorts them, then sweeps the line to compute covered intervals.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

typedef long long ll;
int main() {
  ll n;
  scanf("%lld", &n);
  std::vector<std::pair<ll, ll>> a; // Events: {coordinate, delta}
  for (ll p = 0; p < n; p++) {
    ll l, r;
    scanf("%lld %lld", &l, &r);
    a.push_back(std::make_pair(l, 1));      // Start of segment
    a.push_back(std::make_pair(r + 1, -1)); // End of segment (exclusive)
  }
  sort(a.begin(), a.end()); // Sort events by coordinate
  std::vector<ll> b(n + 1, 0); // Result: b[k] = count of points covered by exactly k segments
  ll active(0); // Current number of active segments
  for (ll p = 0; p < a.size() - 1; p++) {
    active += a[p].second; // Update active segment count
    b[active] += a[p + 1].first - a[p].first; // Accumulate length of current interval
  }
  for (ll p = 1; p <= n; p++) {
    printf("%lld ", b[p]);
  };
  puts("");
  return 0;
}


// https://github.com/VaHiX/codeForces/