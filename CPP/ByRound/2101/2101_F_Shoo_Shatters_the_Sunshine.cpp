// Problem: CF 2101 F - Shoo Shatters the Sunshine
// https://codeforces.com/contest/2101/problem/F

/*
F. Shoo Shatters the Sunshine

Problem: Given a tree with n vertices, each vertex can be colored red, blue, or white. 
The coolness of a coloring is defined as the maximum distance between a red and a blue vertex.
Calculate the sum of coolness over all 3^n possible colorings modulo 998244353.

Algorithms/Techniques:
- Tree Dynamic Programming with inclusion-exclusion principle
- DFS on tree to calculate contributions of each edge to total sum
- Fast exponentiation for modular arithmetic
- Memoization in DP transitions

Time Complexity: O(n^2) per test case, where n is the number of vertices
Space Complexity: O(n) for storing graph, arrays, and recursion stack
*/
#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <vector>

#define ll long long
using namespace std;
const int MAXN = 6005, MOD = 998244353;
vector<int> G[MAXN], a[MAXN]; // G stores adjacency list, a stores information about subtree nodes
ll p2[MAXN], p3[MAXN];        // p2[i] = 2^i mod MOD, p3[i] = 3^i mod MOD
int b[MAXN];
void solve() {
  int n;
  cin >> n;
  for (int i = 1; i < 2 * n; ++i)
    G[i].clear(); // Clear the graph before processing each test case
  for (int i = 1, u, v; i < n; ++i)  // Read edges and construct tree with virtual nodes
    cin >> u >> v, G[u].push_back(n + i), G[v].push_back(n + i),
        G[n + i] = {u, v}; // Add virtual nodes to handle edge computations
  ll ans = 0;
  for (int rt = 1; rt < 2 * n; ++rt) {  // Try each node as root
    int m = 0;
    for (int u : G[rt]) {
      int k = 0;
      function<void(int, int, int)> dfs = [&](int x, int fz, int d) {
        if (d > k)
          k = d, a[d].push_back(0); // Expand array to fit new depth level
        if (x <= n)
          ++a[d].back(), ++b[d];   // Count number of real nodes at depth d
        for (int y : G[x])
          if (y ^ fz)
            dfs(y, x, d + 1);        // Continue DFS traversal
      };
      dfs(u, rt, 1), m = max(m, k);  // Traverse subtree and find maximum depth
    }
    array<ll, 6> f = {0, 0, 0, 0, 0, 0}, g;  // DP state arrays for different combinations
    for (int i = m; i >= 1; --i)
      if (b[i]) {
        int c = b[i];
        // Compute transition values using DP
        g[0] = (f[0] * p2[c] + (p2[c] - 1)) % MOD;
        g[3] = (f[3] * p2[c] + (p2[c] - 1) * i) % MOD;
        ll w1 = p2[c] - 1, w2 = p3[c] + MOD - p2[c];
        // Adjust for current node contributions
        for (int x : a[i]) {
          w1 = (w1 - (p2[x] - 1)) % MOD;
          w2 = (w2 - (p3[x] - p2[x]) * p2[c - x]) % MOD;
        }
        w1 = (w1 + MOD) % MOD, w2 = (w2 + MOD) % MOD;
        g[1] = (f[1] * p2[c] + w1) % MOD;
        g[4] = (f[4] * p2[c] + w1 * i) % MOD;
        g[2] = (f[2] * p3[c] + f[0] * w2 + f[1] * (p3[c] + MOD - p2[c]) +
                (w2 + MOD - w1)) %
               MOD;
        g[5] =
            (f[5] * p3[c] + f[3] * w2 + f[4] * (p3[c] + MOD - p2[c]) +
             (f[0] * w2 + f[1] * (p3[c] + MOD - p2[c]) + (w2 + MOD - w1) * 2) %
                 MOD * i) %
            MOD;
        f.swap(g); // Swap current and next state for DP iteration
      }
    if (rt <= n)
      ans = (ans + f[5] * 3 + f[3] + f[4]) % MOD; // Add contribution when node is real
    else
      ans = (ans + f[5]) % MOD;   // Otherwise just add f[5]
    for (int i = 1; i <= m; ++i)
      a[i].clear(), b[i] = 0;     // Reset arrays for next iteration
  }
  ans = (MOD + 1) / 2 * ans % MOD;   // Multiply by inverse of 2 mod MOD (since we count twice)
  cout << ans << "\n";
}
signed main() {
  ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  for (int i = p2[0] = p3[0] = 1; i < MAXN; ++i) // Precompute powers of 2 and 3
    p2[i] = p2[i - 1] * 2 % MOD, p3[i] = p3[i - 1] * 3 % MOD;
  int _;
  cin >> _;
  while (_--)
    solve(); // Process each test case
  return 0;
}


// https://github.com/VaHiX/CodeForces/