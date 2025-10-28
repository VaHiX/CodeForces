// Problem: CF 1923 B - Monsters Attack!
// https://codeforces.com/contest/1923/problem/B

/*
B. Monsters Attack!
time limit per test2.5 seconds
memory limit per test256 megabytes

Algorithm: Greedy with sorting and simulation
Approach:
- Sort monsters by their initial position (x_i) in ascending order.
- Simulate the process of firing bullets and moving monsters.
- At each time step, calculate how many bullets are needed to kill monsters that are within range,
  considering the movement of monsters.
- Use a greedy strategy: fire all available bullets (k per second) at the monster with highest health
  (or lowest x coordinate if tied) so as to ensure no monster reaches position 0.

Time Complexity: O(n log n) due to sorting, where n is the number of monsters.
Space Complexity: O(n) for storing monster data.

*/

#include <algorithm>
#include <cstdio>
#include <utility>
#include <vector>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, k;
    scanf("%lld %lld", &n, &k);
    std::vector<std::pair<ll, ll>> v(n); // pair<distance_from_origin, health>
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &v[p].second); // read health
    }
    for (ll p = 0; p < n; p++) {
      ll x;
      scanf("%lld", &x);
      v[p].first = (x > 0 ? x : -x); // use absolute value as distance from origin
    }
    sort(v.begin(), v.end()); // Sort by distance from origin

    ll prev(0), rem(0); // 'prev' stores previous time index; 'rem' tracks remaining bullets available
    bool ans(true);
    for (ll p = 0; ans && p < n; p++) {
      rem += k * (v[p].first - prev); // Add bullets accumulated since last monster was processed
      rem -= v[p].second;             // Remove bullets used on current monster
      prev = v[p].first;              // Update time index to current monster's position
      if (rem < 0) {                  // If not enough bullets to kill the current monster
        ans = false;
      }
    }
    puts(ans ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/