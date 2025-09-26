/*
 * Problem URL : https://codeforces.com/problemset/problem/2062/F
 * Submit Date : 2025-08-23
 */

#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll N = 3007;
ll T, n, f[N][3], ans[N];
pair<ll, ll> a[N];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> T;
  while (T--) {
    cin >> n;
    memset(f, 0x3f, sizeof(f));
    memset(ans, 0x3f, sizeof(ans));
    f[0][0] = 0;
    for (int x, y, i = 1; i <= n; ++i) {
      cin >> x >> y;
      a[i] = make_pair(x - y, x + y);
    }
    sort(a + 1, a + 1 + n);
    for (int i = 1; i <= n; ++i) {
      for (int j = i; j > 1; --j) {
        f[j][2] = min(f[j][2], min(f[j - 1][2] + 2 * a[i].second,
                                   f[j - 1][1] + a[i].second - a[i].first));
        f[j][1] = min(f[j][1], min(f[j - 1][1] + 2 * a[i].second,
                                   f[j - 1][0] + a[i].second + a[i].first));
        f[j][0] = min(f[j][0], f[j - 1][0] + 2 * a[i].second);
        ans[j] = min(ans[j], min(f[j - 1][2] + 2 * (a[i].first + a[i].second),
                                 f[j - 1][1] + a[i].first + a[i].second));
      }
      f[1][0] = min(f[1][0], 2 * (a[i].second - a[i].first));
      f[1][1] = min(f[1][1], a[i].second - a[i].first);
    }
    for (int i = 2; i <= n; ++i)
      cout << ans[i] / 2 << ' ';
    cout << '\n';
  }
  return 0;
}