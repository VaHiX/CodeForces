/*
 * Problem URL : https://codeforces.com/problemset/problem/1990/E1
 * Submit Date : 2025-08-13
 */

#include <bits/stdc++.h>

const int MAXN = 5005;
std::vector<int> adj[MAXN];
int idx[MAXN], dep[MAXN], fa[MAXN];
bool vis[MAXN];
int N;

inline int query(int x) {
  std::cout << "? " << x << std::endl;
  std::cin >> x;
  return x;
}

inline void Ans(int x) { std::cout << "! " << x << std::endl; }

void dfs(int u) {
  for (int v : adj[u])
    if (!dep[v])
      fa[v] = u, dep[v] = dep[u] + 1, dfs(v);
}

void fillTree(int u) {
  vis[u] = true;
  for (int v : adj[u])
    if (v != fa[u] && !vis[v])
      fillTree(v);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int testCase = 1;
  std::cin >> testCase;
  while (testCase--) {
    std::cin >> N;
    for (int i = 1; i <= N; ++i)
      idx[i] = i, dep[i] = 0, vis[i] = false, fa[i] = i;
    for (int i = 1; i <= N; ++i)
      adj[i].clear();
    for (int i = 1, u, v; i < N; ++i) {
      std::cin >> u >> v;
      adj[u].push_back(v), adj[v].push_back(u);
    }

    dep[1] = 1, dfs(1);
    std::sort(idx + 1, idx + 1 + N,
              [&](int i, int j) { return dep[i] > dep[j]; });
    bool ok = true;
    for (int i = 1; i <= N && ok; ++i) {
      int u = idx[i];
      if (vis[u])
        continue;

      int pa = u;
      for (int j = 1; j <= 70 && (pa != 1); ++j)
        pa = fa[pa];
      if (!query(pa)) {
        fillTree(pa);
        continue;
      }

      int lim = dep[u] - dep[pa] + 1;
      for (int j = 1; j <= lim; ++j) {
        if (query(idx[1])) {
          Ans(idx[1]), ok = false;
          break;
        }

        if (!query(pa)) {
          Ans(fa[fa[pa]]), ok = false;
          break;
        }
      }

      if (ok)
        Ans(1), ok = false;
    }
  }

  return 0;
}