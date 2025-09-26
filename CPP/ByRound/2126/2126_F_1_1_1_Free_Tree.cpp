// Problem: CF 2126 F - 1-1-1, Free Tree!
// https://codeforces.com/contest/2126/problem/F

/*
F. 1-1-1, Free Tree!
Problem: Given a tree with colored vertices and weighted edges, compute the sum of edge costs after each color change query.

Algorithm:
- Build a tree from input edges.
- Use DFS to traverse the tree and maintain a map for each node storing how many edges of certain weight connect nodes with specific colors.
- When a vertex color changes:
  - Update the map to reflect new color relationships.
  - Adjust total cost accordingly.
- This efficiently handles updates in O(1) time after initial preprocessing.

Time Complexity: O(n + q)
Space Complexity: O(n)

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
vector<pair<ll, ll>> G[N]; // Adjacency list: {neighbor, edge_weight}
map<ll, ll> mp[N];        // For each node, stores count of edges with specific color leading to it
void dfs(ll x) {
  for (pair<ll, ll> y : G[x]) {
    if (y.first != fa[x]) {
      fa[y.first] = x;
      w[y.first] = y.second;
      mp[x][a[y.first]] += y.second;  // Count edges going from parent x to child y based on color
      dfs(y.first);
    }
  }
  ans -= mp[x][a[x]];  // Subtract cost of edges from current node to children with same color (cost should be zero)
}
int main() {
  ios::sync_with_stdio(0);
  cin >> T;
  while (T--) {
    cin >> n >> q;
    ans = 0;
    for (ll i = 1; i <= n; i++) {
      cin >> a[i];
      G[i].clear();
      mp[i].clear();
    }
    for (ll i = 1; i < n; i++) {
      cin >> u >> v >> c;
      ans += c;  // Initially, sum all edge weights
      G[u].push_back({v, c});
      G[v].push_back({u, c});
    }
    dfs(1);  // Initialize the maps with initial edge counts.
    for (ll i = 1; i <= q; i++) {
      cin >> v >> x;
      ans += mp[v][a[v]];                  // Add cost of current color change at node v
      ans -= mp[v][x];                     // Subtract cost that would be due to new color x
      ans += mp[fa[v]][a[fa[v]]];         // Add existing cost of parent edge with current parent color
      mp[fa[v]][a[v]] -= w[v];             // Remove old entry from parent's map
      mp[fa[v]][x] += w[v];                // Add new entry for updated color in parent's map
      ans -= mp[fa[v]][a[fa[v]]];         // Subtract cost of updated parent edge with new parent color
      a[v] = x;                            // Update vertex color
      cout << ans << "\n";                 // Output new total cost
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/