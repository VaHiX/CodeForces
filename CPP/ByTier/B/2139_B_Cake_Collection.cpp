/*
 * Problem URL : https://codeforces.com/contest/2139/problem/B
 * Submit Date : 2025-09-09
 */

#include <bits/stdc++.h>

using namespace std;
#define int long long
#define basbosa ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

signed main() {
  basbosa int t;
  cin >> t;
  while (t--) {
    int n, m, ans = 0;
    cin >> n >> m;
    vector<int> v(n);
    for (auto &i : v)
      cin >> i;
    sort(v.rbegin(), v.rend());
    for (int i = 0; i < n && m; i++, m--) {
      ans += (v[i] * m);
    }
    cout << ans;
    cout << '\n';
  }
}