// Problem: CF 2052 J - Judicious Watching
// https://codeforces.com/contest/2052/problem/J

/*
J. Judicious Watching
Algorithms/Techniques: 
  - Sorting tasks by deadline to optimally assign them.
  - Preprocessing task intervals using a greedy approach to find available time slots.
  - Binary search on precomputed episode counts for each query.

Time Complexity: O(n log n + m + q * log m)
Space Complexity: O(n + m + q)

*/

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
long long int t, n, m, q, e[200005], now, tot;
pair<long long int, long long int> task[200005];
vector<long long int> v;
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> t;
  while (t--) {
    cin >> n >> m >> q;
    for (int i = 0; i < n; ++i)
      cin >> task[i].second;  // Read task durations
    for (int i = 0; i < n; ++i)
      cin >> task[i].first;   // Read deadlines
    for (int i = 0; i < m; ++i)
      cin >> e[i];            // Read episode lengths
    sort(task, task + n);     // Sort tasks by deadline
    now = 1e18;
    // Process tasks backward to calculate minimum start time
    for (int i = n - 1; i >= 0; --i) {
      now = min(now, task[i].first);
      task[i] = make_pair(now - task[i].second + 1, now);  // Set interval [start, end]
      now = task[i].first - 1;                             // Update new available start point
    }
    v.clear();
    v.push_back(0);
    now = 1, tot = 0;
    task[n] = make_pair(1e18, 1e18);  // Sentinel to avoid boundary checks
    // Compute how many episodes Jill can watch before reaching each time slot
    for (int i = 0; i < m; ++i) {
      while (now + e[i] > task[tot].first)
        now += task[tot].second - task[tot].first + 1, ++tot; // Move to next task interval
      now += e[i];     // Watch the current episode
      v.push_back(now - 1);  // Record end time after this episode
    }
    while (q--) {
      long long int tk;
      cin >> tk;
      int l = 0, r = m, mid;
      // Binary search for largest index where v[mid] <= tk
      while (l < r) {
        mid = l + r + 1 >> 1;
        if (v[mid] <= tk)
          l = mid;
        else
          r = mid - 1;
      }
      cout << l << ' ';
    }
    cout << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/