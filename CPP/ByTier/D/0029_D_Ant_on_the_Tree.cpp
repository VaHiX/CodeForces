/*
 * Problem URL : https://codeforces.com/problemset/problem/29/D
 * Submit Date : 2025-08-12
 */

#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> adj;
int n, i, u, v;
vector<int> ans;
bool dfs(int aim, int v, int p) {
  if (aim == v)
    return 1;
  for (auto &to : adj[v])
    if (to != p && dfs(aim, to, v)) {
      ans.push_back(v);
      return 1;
    }
  return 0;
}
int main() {
  ios::sync_with_stdio(0);
  cin >> n;
  adj.resize(n + 1);
  for (i = 0; i < n - 1; ++i) {
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  ans.push_back(1);
  u = 1;
  while (cin >> v) {
    dfs(u, v, 0);
    u = v;
  }
  dfs(u, 1, 0);
  if (ans.size() != 2 * n - 1)
    cout << -1;
  else
    for (auto &x : ans)
      cout << x << " ";
}