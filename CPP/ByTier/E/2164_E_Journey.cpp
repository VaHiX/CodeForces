// Problem: CF 2164 E - Journey
// https://codeforces.com/contest/2164/problem/E

/*
 * Problem: E. Journey
 * 
 * Purpose: Find minimum cost to mark all edges at least once and return to vertex 1.
 * 
 * Algorithm:
 * - Use Union-Find (Disjoint Set Union) to build a spanning tree and track odd-degree vertices.
 * - For each edge:
 *   - If both endpoints are in same component, update min weight for that component.
 *   - Otherwise, merge components and record new node properties.
 * - Process nodes in reverse order, updating values based on parent nodes, and sum up costs for nodes
 *   marked as needing extra cost (odd-degree nodes).
 * 
 * Time Complexity: O(m * α(n)) where α is inverse Ackermann function, effectively nearly constant.
 * Space Complexity: O(n)
 */
#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

using namespace std;
#define ll long long
const int MAXN = 2e6 + 5;
int n, m, fa[MAXN], val[MAXN], ff[MAXN];
bool vis[MAXN], ok[MAXN];
vector<array<int, 3>> E;

// Find root with path compression
inline int find(int x) {
  while (x ^ fa[x])
    x = fa[x] = fa[fa[x]]; // Path compression
  return x;
}

void solve() {
  cin >> n >> m;
  ll ans = 0;
  // Initialize data structures
  for (int i = 1; i <= 2 * n; i++)
    fa[i] = i, ff[i] = 0, vis[i] = ok[i] = false, val[i] = 1e9;
  E.resize(m);
  
  // Read edges and accumulate total weight
  for (auto &[u, v, w] : E)
    cin >> u >> v >> w, vis[u] ^= 1, vis[v] ^= 1, ans += w; // Toggle degrees and add weight
  
  int k = n; // Start of new nodes in union-find structure
  for (auto [u, v, w] : E) {
    u = find(u), v = find(v); // Find roots
    if (u == v)
      val[u] = min(val[u], w); // Update minimum edge weight in component
    else {
      ++k;
      // Mark this new node as needing a cost if both subtrees have odd-degree nodes
      if (vis[u] && vis[v])
        ok[k] = true;
      vis[k] = vis[u] ^ vis[v]; // Degree of new node
      fa[u] = fa[v] = ff[u] = ff[v] = k; // Union and set parent
      val[k] = w; // Store edge weight at new node
    }
  }
  
  // Process nodes in reverse order to propagate minimum weights
  for (int i = 2 * n - 1; i >= 1; i--) {
    if (ff[i])
      val[i] = min(val[i], val[ff[i]]); // Propagate min weight to parents
    if (ok[i])
      ans += val[i]; // Add cost for odd-degree nodes
  }
  cout << ans << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int T;
  cin >> T;
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/