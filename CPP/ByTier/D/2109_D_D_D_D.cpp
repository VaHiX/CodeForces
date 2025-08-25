/*
 * Problem URL : https://codeforces.com/problemset/problem/2109/D
 * Submit Date : 2025-08-17
 */

/*
 * Problem URL : https://codeforces.com/problemset/problem/2109/D
 * Submit Date : 2025-08-17
 */

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void solve() {
  int n, m, l;
  cin >> n >> m >> l;
  vector<int> a(l), dis[2];
  for (auto &i : a)
    cin >> i;
  dis[0] = vector<int>(n + 1, INT_MAX);
  dis[1] = dis[0];
  vector<vector<int>> adj(n + 1);
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  int msum[2] = {0, 0};
  for (auto k : a) {
    int l = msum[0] + k;
    int r = msum[1] + k;
    msum[l % 2] = max(msum[l % 2], l);
    msum[r % 2] = max(msum[r % 2], r);
  }
  dis[0][1] = 0;
  vector<int> cq{1};
  for (int i = 1; cq.size(); ++i) {
    vector<int> nq;
    int j = i % 2;
    for (auto u : cq) {
      for (auto nxt : adj[u]) {
        if (dis[j][nxt] != INT_MAX)
          continue;
        dis[j][nxt] = i;
        nq.push_back(nxt);
      }
    }
    cq = nq;
  }
  for (int i = 1; i <= n; ++i) {
    int good = 0;
    for (int p = 0; p <= 1; ++p) {
      if (dis[p][i] <= msum[p]) {
        good = 1;
      }
    }
    cout << good;
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}
