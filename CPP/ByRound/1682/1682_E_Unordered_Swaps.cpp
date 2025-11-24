// Problem: CF 1682 E - Unordered Swaps
// https://codeforces.com/contest/1682/problem/E

/*
Algorithm/Technique: 
This problem involves finding a valid order of swaps to sort a permutation, given that the number of swaps is exactly m and the swaps are a subset of the minimum required sequence. 

The approach uses:
1. Finding cycles in the permutation using DFS.
2. For each cycle, we sort the edges in the order that respects the cycle structure.
3. Building a directed graph of dependencies among swaps.
4. Performing topological sort on the graph to get the correct order.

Time Complexity: O(n log n + m) where n is the size of permutation, and m is the number of swaps.
Space Complexity: O(n + m) for storing the permutation, adjacency lists, and auxiliary arrays.

*/
#include <string.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
const int N = 200005;
typedef long long ll;
int n, m, p[N], vis[N], pos[N];
vector<pair<int, int>> a[N];  // Stores adjacent swaps for each position
vector<int> G[N], ans;        // Graph for topological sort
void dfs(int u) {
  if (vis[u])
    return;
  vis[u] = 1;
  for (auto v : G[u])
    dfs(v);
  ans.push_back(u);  // Add to topological order
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= n; ++i)
    cin >> p[i];
  for (int i = 1; i <= m; ++i) {
    int u, v;
    cin >> u >> v;
    a[u].emplace_back(v, i);  // Store swap index and node it connects to
    a[v].emplace_back(u, i);
  }
  for (int i = 1; i <= n; ++i) {
    if (vis[i])
      continue;
    vector<int> A;
    // Traverse the cycle
    for (int u = i; !vis[u]; u = p[u]) {
      A.push_back(u);
      vis[u] = 1;
    }
    // Set positions within the cycle
    for (int j = 0; j < (int)A.size(); ++j)
      pos[A[j]] = j;
    // Sort edges for each node in cycle by their position in cycle
    for (auto u : A) {
      sort(a[u].begin(), a[u].end(), [&](pair<int, int> x, pair<int, int> y) {
        return (pos[x.first] - pos[u] + A.size()) % A.size() <
               (pos[y.first] - pos[u] + A.size()) % A.size();
      });
      // Build graph: edge from swap i+1 to swap i
      for (int j = 0; j < (int)a[u].size() - 1; ++j)
        G[a[u][j + 1].second].push_back(a[u][j].second);
    }
  }
  memset(vis, 0, sizeof(vis));
  for (int i = 1; i <= m; ++i)
    if (!vis[i])
      dfs(i);
  for (auto x : ans)
    cout << x << ' ';
  cout << '\n';
  return 0;
}


// https://github.com/VaHiX/CodeForces/