// Problem: CF 1843 D - Apple Tree
// https://codeforces.com/contest/1843/problem/D

/*
D. Apple Tree
Algorithms/Techniques: Tree traversal (DFS), preprocessing descendants count, offline queries

Time Complexity: O(n + q) per test case
Space Complexity: O(n) per test case

The problem involves a rooted tree where apples fall from specified nodes.
We precompute for each node how many descendants it has (including itself).
For any two nodes x and y, the answer is the product of their descendant counts.
This works because an apple at node u can fall from any of its descendants,
and the number of such descendants determines possible falling positions.
*/

#include <cstdio>
#include <vector>
typedef long long ll;

// DFS to compute number of descendants for each node
void dfs(ll cur, ll from, const std::vector<std::vector<ll>> &g,
         std::vector<ll> &desc) {
  const std::vector<ll> neighbors = g[cur];
  // If current node is not root and has only one neighbor (i.e., leaf)
  if (cur > 1 && neighbors.size() == 1) {
    desc[cur] = 1; // Only itself
    return;
  }
  for (ll p = 0; p < neighbors.size(); p++) {
    ll x = neighbors[p];
    if (x == from) {
      continue; // Skip parent to avoid going back
    }
    dfs(x, cur, g, desc); // Recursively process child
    desc[cur] += desc[x]; // Accumulate descendant count
  }
  return;
}

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    std::vector<std::vector<ll>> g(n + 1, std::vector<ll>());
    for (ll p = 1; p < n; p++) {
      ll x, y;
      scanf("%lld %lld", &x, &y);
      g[x].push_back(y); // Build adjacency list
      g[y].push_back(x);
    }
    std::vector<ll> d(n + 1, 0); // Descendant count for each node
    dfs(1, 1, g, d); // Start DFS from root
    ll q;
    scanf("%lld", &q);
    while (q--) {
      ll x, y;
      scanf("%lld %lld", &x, &y);
      printf("%lld\n", d[x] * d[y]); // Product gives number of pairs
    }
  }
}


// https://github.com/VaHiX/codeForces/