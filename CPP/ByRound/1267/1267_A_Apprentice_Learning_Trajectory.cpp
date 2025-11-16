// Problem: CF 1267 A - Apprentice Learning Trajectory
// https://codeforces.com/contest/1267/problem/A

/*
 * Problem: Apprentice Learning Trajectory
 * 
 * Task: Abigail wants to maximize the number of swords she can produce by apprenticing
 *       under n masters. Each master has a time interval [a_i, b_i] during which
 *       she can work and requires t_i continuous minutes to make one sword.
 *
 * Algorithm:
 *   - Sweep line technique combined with a priority queue to track active intervals.
 *   - Events are created for start and end of each interval.
 *   - At each event, the current maximum number of swords is computed based on
 *     the remaining time units available in active masters' intervals.
 *
 * Time Complexity: O(n log n) due to sorting and priority queue operations.
 * Space Complexity: O(n) for storing events and auxiliary arrays.
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>

using namespace std;
const int N = 2e5 + 5;
#define fi first
#define se second
typedef long long ll;
priority_queue<pair<ll, int>> q; // Priority queue to keep track of active intervals' t values (negative for max heap)
int n;
ll t[N];
bool v[N]; // Visited array to mark end events processed

// Structure to hold interval events
struct ch {
  ll x;
  int id, tp;
  bool operator<(const ch &a) const { return x < a.x; } // Sort by time
} p[N * 2];

ll ans;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  ll x, y;
  for (int i = 1; i <= n; i++) {
    cin >> x >> y >> t[i];
    p[i * 2 - 1] = {x + t[i], i, 1}, p[i * 2] = {y, i, -1}; // Add start and end events
  }
  sort(p + 1, p + n * 2 + 1); // Sort all events by time

  x = 0; // Current time pointer
  for (int i = 1; i <= n * 2; i++) {
    while (q.size() && v[q.top().se]) // Remove stale entries from heap
      q.pop();
    if (q.size()) {
      ll delta = p[i].x - x;
      ans += delta / (-q.top().fi); // Count how many full time units we can spend
      x += ((delta / (-q.top().fi))) * (-q.top().fi); // Advance current time
    }
    if (p[i].tp == 1) { // Start event: add this interval to active set
      q.push({-t[p[i].id], p[i].id});
      if (x + t[p[i].id] <= p[i].x)
        x = p[i].x, ans++; // If we can complete a sword immediately
    } else // End event: mark interval as closed
      v[p[i].id] = 1;
  }
  cout << ans << '\n';
  return 0;
}


// https://github.com/VaHiX/codeForces/