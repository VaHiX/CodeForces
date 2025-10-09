/*
 * Problem URL : https://codeforces.com/problemset/problem/1760/G
 * Submit Date : 2025-08-21
 */

#include <bits/stdc++.h>
using namespace std;
int S, T;
map<int, vector<pair<int, int>>> to;
set<int> g;
void dfs1(int u, int f, int x) {
  g.insert(x);
  for (auto [w, wt] : to[u]) {
    if (w != f && w != T)
      dfs1(w, u, x ^ wt);
  }
}
int dfs2(int u, int f, int x) {
  int suc = 0;
  for (auto [w, wt] : to[u]) {
    if (w == f)
      continue;
    if (g.count(x ^ wt))
      return 1;
    int aabb;
    suc |= dfs2(w, u, x ^ wt);
  }
  return suc;
}
int main() {
  int t, u, v, w, n;
  scanf("%d", &t);
  while (t--) {
    scanf("%d%d%d", &n, &S, &T);
    g.clear();
    to.clear();
    for (int i = 1; i < n; i++) {
      scanf("%d%d%d", &u, &v, &w);
      to[u].push_back({v, w});
      to[v].push_back({u, w});
    }
    dfs1(S, 0, 0);
    puts(dfs2(T, 0, 0) ? "YES" : "NO");
  }
}
