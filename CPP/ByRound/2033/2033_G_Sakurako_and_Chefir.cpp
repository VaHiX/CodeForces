// Problem: CF 2033 G - Sakurako and Chefir
// https://codeforces.com/contest/2033/problem/G

/*
G. Sakurako and Chefir

Algorithms/Techniques: 
Heavy-Light Decomposition with Binary Lifting and Preprocessing for Tree Diameter Queries.
Uses binary lifting to quickly find ancestor nodes and track maximum distances using precomputed values.

Time Complexity:
- Preprocessing per test case: O(n log n)
- Each query: O(log n)
Overall: O(n log n + q log n) per test case

Space Complexity:
- O(n log n) for storing binary lifting tables (fa, mx)
*/

#include <stdio.h>
#include <algorithm>

using namespace std;
const int N = 2e5 + 5, M = 4e5 + 5;
int head[N], cnt;
struct node {
  int nxt, to;
} g[M];
void add(int u, int v) {
  g[++cnt] = {head[u], v};
  head[u] = cnt;
}
int fa[N][20], mx[N][20], mxdep[N], dep[N];
void dfs1(int u, int f) {
  mxdep[u] = dep[u] = dep[f] + 1;
  int d1 = -1e9, d2 = -1e9;
  for (int i = head[u]; i; i = g[i].nxt) {
    int v = g[i].to;
    if (v == f)
      continue;
    dfs1(v, u);
    mxdep[u] = max(mxdep[u], mxdep[v]);
    if (mxdep[v] - dep[u] > d1)
      d2 = d1, d1 = mxdep[v] - dep[u];
    else if (mxdep[v] - dep[u] > d2)
      d2 = mxdep[v] - dep[u];
  }
  for (int i = head[u]; i; i = g[i].nxt) {
    int v = g[i].to;
    if (v == f)
      continue;
    // Precompute max distances for each child node with regard to the current node as parent
    mx[v][0] = 1 + (mxdep[v] - dep[u] == d1 ? d2 : d1);
  }
}
void dfs2(int u, int f) {
  for (int i = head[u]; i; i = g[i].nxt) {
    int v = g[i].to;
    if (v == f)
      continue;
    fa[v][0] = u; // Set immediate parent
    for (int i = 1; i < 20; i++) {
      // Binary lifting: compute 2^i-th ancestor and max distance
      fa[v][i] = fa[fa[v][i - 1]][i - 1];
      mx[v][i] = max(mx[v][i - 1], mx[fa[v][i - 1]][i - 1] + (1 << i - 1));
    }
    dfs2(v, u);
  }
}
int n, q;
signed main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
      head[i] = 0;
    cnt = 0;
    for (int i = 1, u, v; i < n; i++) {
      scanf("%d%d", &u, &v);
      add(u, v);
      add(v, u);
    }
    dfs1(1, 0); // Preprocessing tree structure and max depths
    dfs2(1, 0); // Set up binary lifting tables
    scanf("%d", &q);
    while (q--) {
      int u, k;
      scanf("%d%d", &u, &k);
      k = min(k, dep[u] - 1); // Stamina cannot exceed path to root
      int ans = max(k, mxdep[u] - dep[u]), sum = 0; // Base answer is either k, or the depth from u's current level
      for (int i = 19; ~i; i--)
        if (k & (1 << i)) {
          ans = max(ans, mx[u][i] + sum); // Update answer with max possible distance
          u = fa[u][i]; // Jump to 2^i-th ancestor
          sum += 1 << i; // Keep track of path traveled
        }
      printf("%d ", ans);
    }
    putchar('\n');
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/