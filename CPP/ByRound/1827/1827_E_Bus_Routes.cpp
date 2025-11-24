// Problem: CF 1827 E - Bus Routes
// https://codeforces.com/contest/1827/problem/E

/*
 * Problem: E. Bus Routes
 * Purpose: Determine if all pairs of cities in a tree can be connected using at most two bus routes.
 * 
 * Algorithms/Techniques: 
 * - Tree DFS with Euler Tour + LCA (Lowest Common Ancestor) using Sparse Table
 * - Identify leaf nodes and track their closest connection point to bus routes
 * - Check for coverage of all leaf nodes by at least one bus route
 * 
 * Time Complexity: O(n * log(n) + m * log(n))
 *   - DFS + LCA preprocessing: O(n * log(n))
 *   - Processing bus routes: O(m * log(n))
 *   - Checking coverage: O(n)
 * Space Complexity: O(n * log(n) + m)
 *   - LCA sparse table: O(n * log(n))
 *   - Other arrays: O(n + m)
 */

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
const int N = 5e5 + 4;
int n, m, dep[N], cnt, dfn[N], siz[N], rt;
vector<int> tr[N];
int st[20][N];  // Sparse table for LCA
int a[N], b[N], c[N], iv[N], p, q;
bool leaf[N];
int vec[N], ok[N];

// DFS to build Euler tour and compute depths
void dfs(int x, int p) {
  st[0][dfn[x] = ++cnt] = dfn[p], iv[cnt] = x, siz[x] = 1;
  for (auto &y : tr[x])
    if (y != p)
      dep[y] = dep[x] + 1, dfs(y, x), siz[x] += siz[y];
}

// Find Lowest Common Ancestor using sparse table
int lca(int u, int v) {
  u = dfn[u], v = dfn[v];
  if (u > v)
    swap(u, v);
  int d = __lg(v - u);
  return iv[min(st[d][u + 1], st[d][v - (1 << d) + 1])];
}

// Check if node x is in the range of node p (used for subtree check)
bool inr(int x) { return dfn[p] <= dfn[x] && dfn[x] < dfn[p] + siz[p]; }

// Main solution function
void sol() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++)
    tr[i].clear();
  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    tr[u].emplace_back(v), tr[v].emplace_back(u);
  }
  for (int i = 0; i < m; i++) {
    cin >> a[i] >> b[i];
    if (a[i] == b[i])
      i--, m--;  // Skip invalid self-loop edges
  }
  if (n < 3)
    return void(cout << (m ? "YES" : "NO\n1 2") << '\n');  // Trivial case for small n

  // Mark non-leaf nodes as root candidate
  for (int i = 1; i <= n; i++) {
    if (tr[i].size() > 1)
      rt = i, leaf[i] = 0;
    else
      leaf[i] = 1, vec[i] = i;  // Initial assignment of leaf node to itself
  }
  
  cnt = 0, dfs(rt, 0);  // Euler tour DFS

  // Build Sparse Table for LCA
  for (int t = 1; t <= __lg(n); t++)
    for (int i = 1, j = 1 << t; j <= n; i++, j++)
      st[t][i] = min(st[t - 1][i], st[t - 1][i + (1 << t - 1)]);

  // Process each bus route to find LCA and adjust vec values
  for (int i = 0; i < m; i++) {
    c[i] = lca(a[i], b[i]);  // Compute LCA of route endpoints
    if (leaf[a[i]] && dep[vec[a[i]]] > dep[c[i]])
      vec[a[i]] = c[i];  // Update leaf's closest node to route
    if (leaf[b[i]] && dep[vec[b[i]]] > dep[c[i]])
      vec[b[i]] = c[i];
  }

  // Find the node with maximum distance from root (the most distanced leaf node)
  p = 0;
  for (int i = 1; i <= n; i++)
    if (leaf[i] && dep[vec[i]] > dep[p])
      p = vec[i], q = i;

  // Reset flags
  for (int i = 1; i <= n; i++)
    if (inr(i))
      leaf[i] = 0;  // Mark nodes inside subtree rooted at p as non-leaf
    else
      ok[i] = 0;    // Reset ok flag

  // Mark how many times a leaf node is connected to a route
  for (int i = 0; i < m; i++) {
    if (leaf[a[i]] && inr(b[i]))
      ok[a[i]]++;
    if (leaf[b[i]] && inr(a[i]))
      ok[b[i]]++;
  }
  
  // Check if any leaf is uncovered by a route
  for (int i = 1; i <= n; i++)
    if (leaf[i] && !ok[i])
      return void(cout << "NO\n" << q << ' ' << i << '\n');

  cout << "YES\n";
}

int main() {
  ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  dep[0] = -1;
  int tc;
  cin >> tc;
  while (tc--)
    sol();
}


// https://github.com/VaHiX/CodeForces/