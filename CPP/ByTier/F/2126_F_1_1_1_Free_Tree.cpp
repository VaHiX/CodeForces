// Problem: CF 2126 F - 1-1-1, Free Tree!
// https://codeforces.com/contest/2126/problem/F

/*
F. 1-1-1, Free Tree!
Algorithms/Techniques: Tree DFS traversal, Edge cost calculation based on vertex colors, Efficient updates with map-based tracking of color contributions.

Time complexity: O(n + q * log n) per test case due to DFS and map operations.
Space complexity: O(n) for storing graph, parent info, weights, and maps.

Given a tree with n vertices and initial colors assigned to each vertex:
- Each edge has a cost of c if the colors of its endpoints differ, 0 otherwise.
- Support q updates where a vertex's color changes.
- After each update, output total sum of edge costs.

The solution uses DFS to precompute neighbor color contributions and maintain a mapping
of how many times each color contributes to edges from a node. When updating,
we update the mapping efficiently in O(log n) time.
*/
#include <algorithm>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

using namespace std;
typedef long long ll;
const ll N = 2e5 + 5;
ll T, n, q, u, v, c, x, ans, a[N], fa[N], w[N];
vector<pair<ll, ll>> G[N];
map<ll, ll> mp[N];

void dfs(ll x) {
  for (pair<ll, ll> y : G[x]) {
    if (y.first != fa[x]) { // Skip the parent to avoid cycles
      fa[y.first] = x;       // Set parent
      w[y.first] = y.second; // Store edge weight
      mp[x][a[y.first]] += y.second; // Count contribution of child's color to current node
      dfs(y.first);
    }
  }
  ans -= mp[x][a[x]]; // Subtract cost of self-match (if any)
}

int main() {
  ios::sync_with_stdio(0);
  cin >> T;
  while (T--) {
    cin >> n >> q;
    ans = 0; // Reset total cost
    for (ll i = 1; i <= n; i++) {
      cin >> a[i];
      G[i].clear(); // Clear adjacency list
      mp[i].clear(); // Clear maps for this node
    }
    for (ll i = 1; i < n; i++) {
      cin >> u >> v >> c;
      ans += c; // Add initial edge cost
      G[u].push_back({v, c}); // Build adjacency list
      G[v].push_back({u, c});
    }
    dfs(1); // Start DFS from root node 1
    
    for (ll i = 1; i <= q; i++) {
      cin >> v >> x;
      ans += mp[v][a[v]]; // Add old contribution of vertex v's color to its parent
      ans -= mp[v][x]; // Subtract new contribution of updated color
      ans += mp[fa[v]][a[fa[v]]]; // Add contribution of parent's current color
      mp[fa[v]][a[v]] -= w[v]; // Remove old edge weight from parent's map
      mp[fa[v]][x] += w[v]; // Add new edge weight to parent's map
      ans -= mp[fa[v]][a[fa[v]]]; // Subtract contribution of parent's updated color
      a[v] = x; // Update vertex color
      cout << ans << "\n";
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/