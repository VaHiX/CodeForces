// Problem: CF 2172 B - Buses
// https://codeforces.com/contest/2172/problem/B

/*
 * Problem: B. Buses
 * 
 * Purpose: 
 *   Given a road of length ℓ, n buses moving at speed x, and m people at positions p_i,
 *   each person can walk at speed y (where y < x). The goal is to find the minimum time
 *   for each person to reach the end of the road (position ℓ), considering that they can
 *   board buses at their current positions if they are on the same path.
 *
 * Algorithm:
 *   - Process all bus and person positions together using a sweep line approach.
 *   - Sort all events (bus start/end positions and person positions) by their x-coordinate.
 *   - For each event:
 *     - If it's a bus start: update the minimum time to reach the end of the road
 *       from the current position, considering boarding the bus.
 *     - If it's a person: compute the minimum time to reach the end of the road.
 *   - Use a sweep line and dynamic programming to maintain the best possible time
 *     to reach any point along the road.
 *
 * Time Complexity: O((n + m) * log(n + m))
 * Space Complexity: O(n + m)
 */

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <tuple>
#include <vector>

using namespace std;
using ll = long long;
vector<tuple<ll, ll, ll>> v;  // List of events: (position, id, destination)
double res[1 << 19];  // Result array for each person's minimum time

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  
  ll n, m, s, vx, vy;
  cin >> n >> m >> s >> vx >> vy;  // Read input: number of buses, people, road length, bus speed, walking speed

  // Read bus data: start position and end position
  for (ll i = 1, j, k; i <= n; i++) {
    cin >> j >> k;
    v.push_back({j, -1, k});  // -1 indicates a bus start event
  }

  // Read person data: current position
  for (ll i = 1, k; i <= m; i++) {
    cin >> k;
    v.push_back({k, i, -1});  // i indicates person id, -1 as destination not applicable
  }

  // Sort all events by position to simulate the sweep line
  sort(v.begin(), v.end());

  double cur = 1e18;  // Tracks the minimum time to reach the end from any valid position
  for (auto [l, id, r] : v) {  // For each event in sorted order
    if (id == -1) {
      // This is a bus start event
      // Compute the time to take this bus from l to r, then walk from r to s
      cur = min(cur, 1.0 * (s - r) / vy + 1.0 * (r - l) / vx);
    } else {
      // This is a person event
      // Compute the minimum time to reach end from position l directly
      res[id] = min(cur, 1.0 * (s - l) / vy);
    }
  }

  // Output the result for each person
  for (int i = 1; i <= m; i++) {
    cout << fixed << setprecision(12) << res[i] << endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/