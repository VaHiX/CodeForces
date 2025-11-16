// Problem: CF 1893 E - Cacti Symphony
// https://codeforces.com/contest/1893/problem/E

/*
 * Problem: E. Cacti Symphony
 * 
 * Algorithm/Techniques:
 * - Graph decomposition into a cactus (a graph where every edge belongs to at most one simple cycle)
 * - DFS to detect cycles and find their lengths
 * - Modular arithmetic with fast exponentiation
 * 
 * Time Complexity: O(n + m)
 * Space Complexity: O(n + m)
 *
 * The solution uses a DFS traversal to compute cycle lengths and applies
 * combinatorial logic to count valid weight assignments.
 * 
 * Key insight: 
 * - For a cactus graph, we can decompose it into cycles and trees.
 * - Each cycle contributes a factor based on how many ways to color its edges/vertices
 *   such that all vertices and edges satisfy the "good" condition.
 * - For each cycle of length k, there are 2^k - 2 valid assignments (subtracting those that
 *   lead to bad configurations).
 * - The final answer is computed using modular exponentiation and multiplication.
 */

#include <stdio.h>
#include <algorithm>
#include <utility>
#include <vector>

#define pb emplace_back
using namespace std;
typedef long long ll;
const int maxn = 1000100;
const ll mod = 998244353;

// Fast exponentiation with modulo
inline ll qpow(ll b, ll p) {
  ll res = 1;
  for (; p; p >>= 1) {
    if (p & 1)
      res = res * b % mod;
    b = b * b % mod;
  }
  return res;
}

ll n, m, f[maxn], a[maxn], tot;
vector<pair<ll, ll>> G[maxn];
bool vis[maxn];

// Depth-first search to calculate distances and detect cycles
void dfs(int u, int fa) {
  vis[u] = 1;
  for (auto p : G[u]) {
    ll v = p.first, d = p.second;
    if (v == fa)
      continue;
    if (vis[v]) {
      // If v is already visited, then we are on a cycle
      if (f[u] < f[v])
        a[++tot] = f[v] - f[u] + d;
      continue;
    }
    f[v] = f[u] + d;
    dfs(v, u);
  }
}

int main() {
  scanf("%lld%lld", &n, &m);
  ll te = 0, tn = n; // te = total edges, tn = total vertices
  
  // Build adjacency list with extended edges
  for (int i = 1, u, v, d; i <= m; ++i) {
    scanf("%d%d%d", &u, &v, &d);
    te += d + 1, tn += d;
    G[u].pb(v, d + 1), G[v].pb(u, d + 1);
  }

  // If total number of vertices and edges is odd, no valid assignment exists
  if ((n + m) & 1)
    return puts("0"), 0;

  // Start DFS from vertex 1
  dfs(1, -1);
  
  // Calculate remaining number of edges after removing all cycles
  ll br = te;
  for (int i = 1; i <= tot; ++i)
    br -= a[i];

  // Initial answer based on remaining edges
  ll ans = qpow(665496236, br); // Multiplicative inverse of 3 mod 998244353
  
  // Process each cycle
  for (int i = 1; i <= tot; ++i) {
    // Apply formula for cycles
    ans = ans * (qpow(2, a[i]) + ((a[i] & 1) ? mod - 2 : 2)) % mod;
    tn -= a[i]; // Reduce count of vertices used
  }

  // Final multiplication with factor from number of cycles
  ans = ans * qpow(2, tot) % mod * qpow(3, tn) % mod;
  
  printf("%lld\n", ans);
}


// https://github.com/VaHiX/CodeForces/