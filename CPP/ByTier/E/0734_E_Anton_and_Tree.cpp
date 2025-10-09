/*
 * Problem URL : https://codeforces.com/contest/734/problem/E
 * Submit Date : 2025-09-02
 */

#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> G;
vector<int> color;
pair<int, int> rec;
int n;
void dfs(int v, int p, int depth) {
  rec = max(rec, {depth, v});
  for (auto to : G[v]) {
    if (to == p)
      continue;
    if (color[to] == color[v])
      dfs(to, v, depth);
    else
      dfs(to, v, depth + 1);
  }
}
int main() {
  ios::sync_with_stdio(0);
  cin >> n;
  G.resize(n + 1);
  color.resize(n + 1);
  for (int i = 1; i <= n; ++i)
    cin >> color[i];
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    cin >> u >> v;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  dfs(1, 0, 0);
  rec.first = -1;
  dfs(rec.second, 0, 0);
  cout << (1 + rec.first) / 2 << endl;
}