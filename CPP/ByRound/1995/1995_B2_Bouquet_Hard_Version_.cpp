/*
 * Problem URL : https://codeforces.com/problemset/problem/1995/B2
 * Submit Date : 2025-08-13
 */

#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long LL;

void solve() {
  LL n, m;
  cin >> n >> m;
  vector<int> a(n + 1), c(n + 1);
  map<int, LL> mp;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  for (int i = 1; i <= n; i++)
    cin >> c[i], mp[a[i]] = c[i];

  LL res = 0;
  for (auto [u, v] : mp) {
    if (mp.count(u + 1)) {
      LL c = min(mp[u], m / u);
      c += min(mp[u + 1], (m - (LL)c * u) / (u + 1));
      res = max(res, min(m, c * u + min(mp[u + 1], c)));
    } else
      res = max(res, (LL)min(mp[u], m / u) * u);
  }
  cout << res << endl;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);

  int T;
  cin >> T;
  while (T--) {
    solve();
  }
  return 0;
}