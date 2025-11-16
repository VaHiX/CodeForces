// Problem: CF 1765 H - Hospital Queue
// https://codeforces.com/contest/1765/problem/H

/*
Algorithm/Techniques: Topological Sorting with Priority Queue
Time Complexity: O(n^3) - For each of the n patients, we perform a topological sort which takes O(n^2) in worst case.
Space Complexity: O(n^2) - For adjacency list representation of the graph and auxiliary arrays.

This problem involves finding the minimum possible position of each patient in a valid ordering,
given constraints on when they must be seen and which patients must come before others.
We use a modified topological sort approach where for each patient, we determine their earliest possible
position by simulating the process of selecting patients in order, respecting the constraints.
*/

#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;
int n, m;
int p[2005], rd[2005];
vector<int> e[2005];
signed main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= n; ++i)
    cin >> p[i]; // Read the maximum position constraint for each patient
  for (int i = 1; i <= m; ++i) {
    int a, b;
    cin >> a >> b; // Read restriction: patient a must come before patient b
    e[b].push_back(a); // Build adjacency list: b depends on a
  }
  for (int i = 1; i <= n; ++i) {
    fill(rd + 1, rd + n + 1, 0); // Reset in-degree array for each iteration
    for (int j = 1; j <= n; ++j)
      for (int y : e[j])
        ++rd[y]; // Calculate in-degrees for each node
    priority_queue<pair<int, int>> q; // Priority queue to store {max_position, patient_id}
    for (int j = 1; j <= n; ++j)
      if (!rd[j] && j != i) // Add all nodes with in-degree 0 and not the current node
        q.push(make_pair(p[j], j));
    int ans = 0;
    for (int t = n; t >= 1; --t) {
      if (q.empty() || q.top().first < t) { // If no valid node can be selected for position t
        ans = t;
        break;
      }
      int x = q.top().second; // Get the patient with highest max_position from queue
      q.pop();
      for (int y : e[x]) { // Reduce in-degree of neighbors
        --rd[y];
        if (!rd[y] && y != i) // Add neighbor to queue if its in-degree becomes 0 and isn't the target patient
          q.push(make_pair(p[y], y));
      }
    }
    cout << ans << " ";
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/