/*
 * Problem URL : https://codeforces.com/problemset/submit
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define IOS                                                                    \
  ios::sync_with_stdio(0);                                                     \
  cin.tie(0)
void solve() {
  int n, k, t;
  cin >> n >> k;
  vector<pair<int, int>> v;
  for (int i = 0; i < n; i++) {
    cin >> t;
    v.push_back({t, 0});
  }
  for (int i = 0; i < n; i++) {
    cin >> t;
    v.push_back({t, 1});
  }
  sort(v.begin(), v.end());
  int ans = 0, c0 = n, c1 = 0, lst = 0;
  for (auto tt : v) {
    int x = tt.first, y = tt.second;
    if (x > lst && c1 <= k)
      ans = max(ans, x * (c0 + c1));
    lst = x;
    if (y == 0) {
      c0--;
      c1++;
    } else
      c1--;
  }
  cout << ans << endl;
}
signed main() {
  IOS;
  int t = 1;
  cin >> t;
  while (t--)
    solve();
}