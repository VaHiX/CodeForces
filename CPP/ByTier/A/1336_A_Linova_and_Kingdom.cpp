// Problem: CF 1336 A - Linova and Kingdom
// https://codeforces.com/contest/1336/problem/A

/*
 * Problem: A. Linova and Kingdom
 * Purpose: Given a tree structure representing a kingdom with n cities and n-1 roads,
 *          select exactly k cities to develop industry such that the sum of happiness
 *          of all envoys sent to the capital is maximized.
 *
 * Algorithm:
 *   - Build adjacency list representation of the tree.
 *   - Perform DFS from the root (capital, node 1) to compute subtree sizes and depth.
 *   - For each node, calculate its "score" as (subtree_size - depth), which represents
 *     how many tourism cities are on the path from that node to the capital.
 *   - Sort scores in descending order and choose top k to maximize total happiness.
 *
 * Time Complexity: O(n log n) due to sorting.
 * Space Complexity: O(n) for storing the tree and auxiliary arrays.
 */
#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;

// DFS traversal to compute subtree sizes and scores
ll dfs(ll node, ll from, const std::vector<std::vector<ll>> &g, ll depth,
       std::vector<ll> &sv) {
  const std::vector<ll> v = g[node];  // Get neighbors of current node
  ll sz(1);  // Size of subtree rooted at current node (start with 1 for itself)
  for (ll p = 0; p < v.size(); p++) {
    if (v[p] == from) {
      continue;  // Skip parent to avoid cycles
    }
    sz += dfs(v[p], node, g, depth + 1, sv);  // Recursively compute subtree size
  }
  sv[node] = sz - depth;  // Compute score as (subtree size - depth)
  return sz;
}

int main() {
  ll n, k;
  scanf("%lld %lld", &n, &k);
  std::vector<std::vector<ll>> g(n + 1);  // Adjacency list of the tree
  for (ll p = 1; p < n; p++) {  // Read edges
    ll x, y;
    scanf("%lld %lld", &x, &y);
    g[x].push_back(y);
    g[y].push_back(x);
  }
  std::vector<ll> hv(n + 1, 0);  // Stores scores for each node
  dfs(1, 0, g, 1, hv);  // Start DFS from root (capital)
  sort(hv.begin() + 1, hv.end());  // Sort scores in ascending order

  ll total(0);
  for (ll p = k + 1; p <= n; p++) {
    total += hv[p];  // Sum top (n - k) largest scores
  }
  printf("%lld\n", total);  // Output maximum happiness sum
  return 0;
}


// https://github.com/VaHiX/codeForces/