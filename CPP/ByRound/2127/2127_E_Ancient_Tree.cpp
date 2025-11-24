// Problem: CF 2127 E - Ancient Tree
// https://codeforces.com/contest/2127/problem/E

/*
E. Ancient Tree
Algorithms/Techniques: Heavy-light decomposition (HLD), Lowest Common Ancestor (LCA), DFS, Sorting

Time Complexity: O(n * log n) per test case due to sorting and tree traversal
Space Complexity: O(n) for storing the tree structure, color info, and auxiliary arrays

Task:
Find minimum cost coloring of a tree where cutie vertices are defined by LCA properties.
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
const int N = 2e5 + 2;
int T, n, k, c[N], w[N];
bool tag[N];
vector<int> e[N], g[N]; // e: tree edges, g: color groups
int fa[N], siz[N], son[N], num, dfn[N], top[N]; // HLD arrays

// First DFS to compute subtree sizes and heavy children
void dfss(int u) {
  siz[u] = 1, son[u] = 0;
  for (int v : e[u])
    if (v != fa[u]) {
      fa[v] = u;
      dfss(v);
      siz[u] += siz[v];
      if (siz[v] > siz[son[u]])
        son[u] = v;
    }
}

// Second DFS to assign DFS numbers and chain heads for HLD
void dfst(int u, int tp) {
  dfn[u] = ++num, top[u] = tp;
  if (son[u])
    dfst(son[u], tp);
  for (int v : e[u])
    if (v != fa[u] && v != son[u])
      dfst(v, v);
}

// LCA query using HLD
int lca(int u, int v) {
  while (top[u] != top[v])
    dfn[u] > dfn[v] ? u = fa[top[u]] : v = fa[top[v]];
  return dfn[u] < dfn[v] ? u : v;
}

// Propagate colors upward
void dfsc(int u) {
  if (!c[u])
    c[u] = c[fa[u]];
  for (int v : e[u])
    if (v != fa[u])
      dfsc(v);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  c[0] = 1;
  for (cin >> T; T--;) {
    cin >> n >> k;
    for (int i = 1; i <= n; ++i)
      e[i].clear();
    for (int i = 1; i <= k; ++i)
      g[i].clear();
    for (int i = 1; i <= n; ++i)
      cin >> w[i];
    for (int i = 1; i <= n; ++i) {
      cin >> c[i];
      if (c[i])
        g[c[i]].push_back(i);
    }
    fill_n(tag + 1, n, 0);
    for (int i = 1, u, v; i < n; ++i) {
      cin >> u >> v;
      e[u].push_back(v), e[v].push_back(u);
    }
    dfss(1);
    dfst(1, 1);
    for (int i = 1; i <= k; ++i) {
      sort(g[i].begin(), g[i].end(),
           [](int x, int y) { return dfn[x] < dfn[y]; });
      for (int j = 1, l; j < g[i].size(); ++j) {
        l = lca(g[i][j - 1], g[i][j]);
        if (!c[l])
          c[l] = i;
        if (c[l] != i)
          tag[l] = 1;
      }
    }
    dfsc(1);
    long long ans = 0;
    for (int i = 1; i <= n; ++i)
      if (tag[i])
        ans += w[i];
    cout << ans << '\n';
    for (int i = 1; i <= n; ++i)
      cout << c[i] << " \n"[i == n];
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/