// Problem: CF 1614 B - Divan and a New Project 
// https://codeforces.com/contest/1614/problem/B

/*
 * Problem: Divan and a New Project
 * 
 * Purpose: To place n+1 buildings (0 to n) on a coordinate line such that the total
 * walking time for the businessman (at building 0) visiting other buildings a_i times
 * is minimized. The walking time for a visit to building i is 2 * |x_0 - x_i|.
 * 
 * Algorithm:
 * - Sort the buildings based on the number of visits in descending order.
 * - Assign coordinates to buildings alternating between positive and negative values
 *   starting from 1, 2, 3... for odd and even positions respectively.
 * - Coordinates are assigned based on the rank of visits to minimize total distance.
 * 
 * Time Complexity: O(n log n) due to sorting
 * Space Complexity: O(n) for storing the input and result vectors
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
    std::vector<std::pair<ll, ll>> v(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &v[p].first);
      v[p].second = p + 1;
    }
    sort(v.rbegin(), v.rend()); // Sort by number of visits in descending order
    ll total(0);
    std::vector<ll> res(n + 1, 0); // Initialize result array
    for (ll p = 0; p < n; p++) {
      ll num = v[p].first;      // Number of visits for current building
      ll idx = v[p].second;     // Original index of the building
      ll dist = p / 2 + 1;      // Distance to assign based on order
      total += 2 * num * dist;  // Add contribution to total time
      ll pos = p % 2 ? dist : -dist; // Alternate signs for coordinates
      res[idx] = pos;           // Assign coordinate to the building
    }
    printf("%lld\n", total);
    for (ll p = 0; p <= n; p++) {
      printf("%lld ", res[p]);
    }
    puts("");
  }
}


// https://github.com/VaHiX/CodeForces/