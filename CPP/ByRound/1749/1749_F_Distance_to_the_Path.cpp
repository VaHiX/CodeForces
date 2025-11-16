// Problem: CF 1749 F - Distance to the Path
// https://codeforces.com/contest/1749/problem/F

/*
Algorithm: Tree decomposition with binary lifting and BIT (Fenwick Tree) for range updates and point queries
Time Complexity: O((n + m) * log n) where n is the number of vertices and m is the number of queries
Space Complexity: O(n * log n) for storing binary lifting table, DFS information and BITs

The solution uses:
- Binary lifting for LCA (Lowest Common Ancestor) queries
- BIT (Fenwick Tree) for efficient range updates and point queries
- Tree decomposition with subtree information for fast distance queries

Approach:
1. Preprocess the tree with binary lifting and DFS to get:
   - Parent and depth information
   - Subtree sizes and DFS order
2. For updates:
   - For each query of type 2 (update), we find the LCA of u and v
   - We apply range updates using BITs in a way that reflects the distance to the path
3. For queries of type 1:
   - For each vertex, we sum up the contributions of all updates that affect it based on distance
   - This uses both the direct update array and BIT prefix sums

The main idea is to avoid iterating over all nodes when processing a query by leveraging:
- Binary lifting for LCA calculation
- BIT for fast range operations
- Precomputed distance information in the "b" array (which keeps track of direct increments)
*/
#include <stdio.h>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;
const int N = 2e5 + 7;
int n, m, fa[N][20], sz[N], dep[N], dfn[N], times;
vector<int> e[N];
int b[N][21], c[21][N];
void add(int c[], int x, int v) {
  for (; x <= n; x += x & -x) // Update BIT with value v at position x
    c[x] += v;
}
int query(int c[], int x, int res = 0) {
  for (; x; x -= x & -x) // Query prefix sum from 1 to x
    res += c[x];
  return res;
}
void dfs(int u, int p) {
  fa[u][0] = p, dep[u] = dep[p] + 1, sz[u] = 1, dfn[u] = ++times; // Initialize node info before DFS
  for (int i = 1; i < 20; i++) // Precompute binary lifting table
    fa[u][i] = fa[fa[u][i - 1]][i - 1];
  for (auto v : e[u]) { // Visit children
    if (v == p)
      continue;
    dfs(v, u);
    sz[u] += sz[v]; // Compute subtree sizes
  }
}
int lca(int a, int b) {
  if (dep[a] < dep[b])
    swap(a, b); // Ensure a is deeper than b
  for (int i = 19; i >= 0; i--) // Move a up to same level as b
    if (dep[fa[a][i]] >= dep[b])
      a = fa[a][i];
  if (a == b) // If b is ancestor of a
    return a;
  for (int i = 19; i >= 0; i--) // Find LCA
    if (fa[a][i] != fa[b][i])
      a = fa[a][i], b = fa[b][i];
  return fa[a][0];
}
int main() {
  scanf("%d", &n);
  for (int i = 1; i < n; i++) { // Read edges and build adjacency list
    int a, b;
    scanf("%d%d", &a, &b);
    e[a].push_back(b);
    e[b].push_back(a);
  }
  dfs(1, 0); // DFS to precompute tree information
  scanf("%d", &m);
  while (m--) {
    int op, u, v, k, d;
    scanf("%d", &op);
    if (op == 1) { // Type 1: Query value at vertex x
      int x;
      scanf("%d", &x);
      int p = x, ans = 0;
      for (int i = 0; p && i <= 20; i++, p = fa[p][0]) { // Sum up contributions for distance <= 20
        ans += b[p][i];
        ans += query(c[i], dfn[p] + sz[p] - 1) - query(c[i], dfn[p] - 1);
      }
      printf("%d\n", ans);
    } else { // Type 2: Add k to all vertices within distance d from path (u, v)
      scanf("%d%d%d%d", &u, &v, &k, &d);
      int x = lca(u, v); // Find LCA of u and v
      int p = x;
      for (int i = 0; i <= d; i++) { // Propagate k to all vertices within distance d from path
        b[p][d - i] += k;
        if (d - i)
          b[p][d - i - 1] += k;
        if (p == 1) // Special handling for root
          ++i;
        else
          p = fa[p][0]; // Move up to parent
      }
      add(c[d], dfn[u], k); // Update BIT for u
      add(c[d], dfn[v], k); // Update BIT for v
      add(c[d], dfn[x], (-2) * k); // Adjust BIT for LCA (because it was counted twice)
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/