/*
 * Problem URL : https://codeforces.com/problemset/problem/2113/E
 * Submit Date : 2025-08-16
 */

#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
constexpr int MAXN = 1e5 + 1;
vector<int> g[MAXN];
int can[MAXN], cnt[MAXN];
int depth[MAXN], parent[MAXN];

vector<int> get_path(int u, int v) {
  vector<int> a, b;
  while (u != v) {
    if (depth[u] > depth[v]) {
      a.push_back(u);
      u = parent[u];
    } else {
      b.push_back(v);
      v = parent[v];
    }
  }
  vector<int> res = a;
  res.push_back(u);
  res.insert(res.end(), b.rbegin(), b.rend());
  return res;
}

void dfs(int u, int prev = -1) {
  for (int v : g[u]) {
    if (v == prev)
      continue;
    depth[v] = depth[u] + 1;
    parent[v] = u;
    dfs(v, u);
  }
}

void solve() {
  int n, m, x, y;
  cin >> n >> m >> x >> y;
  for (int i = 1; i <= n; i++) {
    g[i].clear();
    can[i] = false;
    cnt[i] = 0;
  }
  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  dfs(1);
  vector<vector<int>> paths(m);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    paths[i] = get_path(u, v);
    reverse(paths[i].begin(), paths[i].end());
    paths[i].pop_back();
  }
  int time = 1;
  vector<int> q, new_q;
  can[x] = true;
  for (int u : g[x]) {
    cnt[u]++;
    q.push_back(u);
  }
  while (!can[y] && time <= n * 2) {
    time++;
    new_q.clear();

    for (int v : q) {
      if (can[v])
        continue;
      if (cnt[v]) {
        new_q.push_back(v);
        can[v] = true;
      }
    }
    q.clear();
    for (int v : new_q) {
      for (int u : g[v]) {
        cnt[u]++;
        q.push_back(u);
      }
    }

    for (int i = (int)paths.size() - 1; i >= 0; i--) {
      int v = paths[i].back();
      paths[i].pop_back();
      if (paths[i].empty()) {
        swap(paths[i], paths.back());
        paths.pop_back();
      }
      if (can[v]) {
        can[v] = false;
        for (int u : g[v]) {
          cnt[u]--;
        }
        q.push_back(v);
      }
    }
  }
  if (!can[y]) {
    cout << "-1\n";
  } else {
    cout << time << "\n";
  }
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  int t;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}
