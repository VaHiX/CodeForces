// Problem: CF 1826 E - Walk the Runway
// https://codeforces.com/contest/1826/problem/E

/*
 * Problem: E. Walk the Runway
 * 
 * Approach:
 * - This problem can be modeled as finding the maximum path in a directed acyclic graph (DAG).
 * - For each city, the ratings of models must be strictly increasing in the order of walking the runway.
 * - We construct a dependency graph: if model u has a lower rating than model v in any city, we add a directed edge from u to v.
 * - Then, we use DFS with memoization (topological sort + dynamic programming) to find the maximum profit path.
 * 
 * Time Complexity: O(m * n * log(n) + n^2)
 * Space Complexity: O(n^2)
 *
 * Algorithms/Techniques:
 * - Graph construction based on strict increasing order of ratings in cities.
 * - Topological sorting using DFS with memoization.
 * - Dynamic Programming on DAG.
 */

#include <algorithm>
#include <bitset>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
typedef long long ll;
const ll MAXN = 5050;
vector<ll> p(MAXN);         // profits for each model
vector<bool> vis(MAXN);     // visited flag for DFS
vector<ll> dfss(MAXN);      // memoization for DFS results
bitset<5001> rel[5001];     // adjacency matrix representing dependencies
int n, m, x;
ll dfs(int v) {
  vis[v] = 1;
  ll mm = 0;
  for (int u = 1; u <= n; u++) {
    if (rel[v][u]) {         // if there's an edge from v to u
      ll del;
      if (vis[u])            // if already visited, use memoized value
        del = dfss[u];
      else
        del = dfs(u);        // otherwise compute recursively
      if (del > mm)
        mm = del;
    }
  }
  dfss[v] = p[v] + mm;       // store the max profit starting from v
  return p[v] + mm;
}
int main() {
  ios::sync_with_stdio(false), cin.tie(nullptr);
  cin >> m >> n;
  vector<pair<int, int>> r[m + 12]; // r[i] stores (rating, model_index) for city i

  // Initialize rel matrix to all 1s (means initially all models can come before others)
  for (int i = 1; i <= n; i++)
    rel[i] = ~rel[i];

  // Read profits of each model
  for (int i = 1; i <= n; i++)
    cin >> p[i];

  // Read ratings for each city and store them in pairs (rating, model index)
  for (int i = 1; i <= m; i++)
    for (int j = 1; j <= n; j++)
      cin >> x, r[i].push_back({x, j});

  // Sort each city's ratings to process in order
  for (int i = 1; i <= m; i++)
    sort(r[i].begin(), r[i].end());

  // Process each city's ordering to build the dependency graph
  for (int k = 1; k <= m; k++) {
    bitset<5001> prev;       // tracks models that appeared in previous ratings
    for (int i = 0; i < n;) {
      int j = i;
      // Group models with same rating and make sure none can come before them
      while (j < n and r[k][i].first == r[k][j].first) {
        rel[r[k][j].second] &= prev;  // Set all models that came after in this city
        ++j;
      }
      // Mark models of current rating as seen
      while (i < j) {
        prev[r[k][i].second] = true;
        ++i;
      }
    }
  }

  ll ret = 0;
  // Compute the maximum profit using DFS from each node
  for (int i = 1; i <= n; i++) {
    ll mm;
    if (vis[i])
      mm = dfss[i];      // if visited already, use memoized result
    else
      mm = dfs(i);       // otherwise compute
    if (mm > ret)
      ret = mm;
  }
  cout << ret << endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/