/*
 * Problem URL : https://codeforces.com/contest/2043/problem/E
 * Submit Date : 2025-08-25
 */

#include <bits/stdc++.h>
using namespace std;
#define lc f << 1
#define rc f << 1 | 1
#define ll long long
#define pii pair<int, int>
#define fi first
#define se second
#define lowbit(x) x & -x
#define gcd(x, y) __gcd(abs(x), abs(y))
const ll inf = LONG_LONG_MAX, mod = 998244353;
const int N = 1e7 + 10, inff = INT_MAX;
const double eps = 1e-9;
void solve() {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> x(n + 1, vector<int>(m + 1, 0)),
      y(n + 1, vector<int>(m + 1, 0));
  vector<vector<int>> a(n + 1, vector<int>(m + 1, 0)),
      b(n + 1, vector<int>(m + 1, 0));
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      cin >> x[i][j];
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      cin >> y[i][j];
  bool f = 1;
  auto check = [&]() -> bool {
    vector<vector<int>> e(n + m + 1);
    vector<bool> v(n + m + 1, 0), in(n + m + 1, 0), vis(n + m + 1, 0);
    auto dfs = [&](int s, auto &dfs) -> bool {
      if (in[s])
        return 0;
      in[s] = 1;
      for (auto it : e[s])
        if (!vis[it] && !dfs(it, dfs))
          return 0;
      in[s] = 0;
      vis[s] = 1;
      return 1;
    };
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++) {
        if (b[i][j])
          e[i].push_back(j + n);
        else
          e[j + n].push_back(i);
        if (a[i][j] && !b[i][j])
          v[i] = 1;
        if (!a[i][j] && b[i][j])
          v[j + n] = 1;
      }
    for (int i = 1; i <= n + m; i++)
      if (v[i] && !dfs(i, dfs))
        if (!dfs(i, dfs))
          return 0;
    return 1;
  };
  while (f) {
    f = 0;
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++) {
        a[i][j] = x[i][j] % 2;
        x[i][j] /= 2;
        if (x[i][j])
          f = 1;
      }
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++) {
        b[i][j] = y[i][j] % 2;
        y[i][j] /= 2;
        if (y[i][j])
          f = 1;
      }
    if (!check()) {
      cout << "No\n";
      return;
    }
  }
  cout << "Yes\n";
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  int T = 1;
  cin >> T;
  while (T--)
    solve();
  return 0;
}