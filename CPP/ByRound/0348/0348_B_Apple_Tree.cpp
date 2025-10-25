/*
 * Problem URL : https://codeforces.com/contest/348/problem/B
 * Submit Date : 2025-09-09
 */

#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> a(n + 1);
  for (int i = 1; i <= n; ++i)
    cin >> a[i];
  vector<vector<int>> edge(n + 1);
  for (int i = 1; i < n; ++i) {
    int u, v;
    cin >> u >> v;
    edge[u].emplace_back(v);
    edge[v].emplace_back(u);
  }
  long long ans = accumulate(a.begin(), a.end(), 0ll);
  long long oo = 2e9;
  long long fix = 1;
  long long Min = 1e18;
  function<void(int, int, long long)> dfs = [&](int u, int p, long long now) {
    fix = fix / __gcd(fix, now) * now;
    if (fix > oo || fix < 0) {
      cout << ans;
      exit(0);
    }
    if (edge[u].size() == 1 && p)
      Min = min(Min, now * a[u]);
    for (auto &v : edge[u]) {
      if (v == p)
        continue;
      dfs(v, u, now * (edge[u].size() - (p > 0)));
    }
  };
  dfs(1, 0, 1);
  cout << ans - Min / fix * fix;
}