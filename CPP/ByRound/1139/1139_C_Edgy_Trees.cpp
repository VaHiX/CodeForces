// Problem: CF 1139 C - Edgy Trees
// https://codeforces.com/contest/1139/problem/C

/*
C. Edgy Trees
Algorithm: DFS to find connected components of red edges, then use inclusion-exclusion principle
Time Complexity: O(n + k)
Space Complexity: O(n)

The problem asks to count the number of sequences of k vertices such that 
the path between consecutive vertices in the sequence uses at least one black edge.
We use the inclusion-exclusion principle:
- Total sequences = n^k
- Subtract sequences that only use red edges (i.e., all paths within connected components of red edges)
For each connected component of red edges, count how many sequences are entirely within this component.
This is done by computing the size of each connected component and raising it to power k.

*/
#include <cstdio>
#include <vector>
typedef long long ll;

// Depth-first search to find the size of connected components formed by red edges
void dfs(ll node, const std::vector<std::vector<ll>> &g,
         std::vector<bool> &been, ll &count) {
  if (been[node]) {
    return;
  }
  been[node] = true;
  ++count; // Increment count for each node visited in the component
  for (ll p = 0; p < g[node].size(); p++) {
    ll x = g[node][p];
    if (been[x]) {
      continue; // Skip already visited nodes
    }
    dfs(x, g, been, count); // Recursively visit neighbors
  }
}

int main() {
  const ll MOD = 1e9 + 7;
  ll n, k;
  scanf("%lld %lld", &n, &k);
  std::vector<std::vector<ll>> g(n + 1); // Adjacency list for red edges only
  for (ll p = 1; p < n; p++) {
    ll x, y, z;
    scanf("%lld %lld %lld", &x, &y, &z);
    if (z) {
      continue; // Skip black edges
    }
    g[x].push_back(y); // Add edge to adjacency list for red edges only
    g[y].push_back(x);
  }
  
  std::vector<ll> h; // Store sizes of connected components formed by red edges
  std::vector<bool> vis(n + 1, 0); // Visited array to track visited nodes
  
  for (ll p = 1; p <= n; p++) {
    if (vis[p]) {
      continue; // Skip already processed nodes
    }
    ll cnt(0);
    dfs(p, g, vis, cnt); // Find size of component starting from node p
    h.push_back(cnt); // Store component size
  }
  
  // Calculate total number of sequences: n^k
  ll total(1);
  for (ll p = 0; p < k; p++) {
    total *= n;
    total %= MOD;
  }
  
  // Subtract invalid sequences (those using only red edges)
  for (ll p = 0; p < h.size(); p++) {
    ll a = h[p];
    for (ll u = 1; u < k; u++) {
      h[p] *= a;
      h[p] %= MOD;
    }
    total -= h[p]; // Subtract number of sequences within this component
    total = ((total % MOD) + MOD) % MOD; // Ensure result is positive
  }
  
  printf("%lld\n", total);
  return 0;
}


// https://github.com/VaHiX/codeForces/