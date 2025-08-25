/*
 * Problem URL : https://codeforces.com/problemset/problem/2132/E
 * Submit Date : 2025-08-21
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 5;
int n, m, q;
ll a[N], b[N];
inline void solve() {
  cin >> n >> m >> q;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  for (int i = 1; i <= m; i++)
    cin >> b[i];
  sort(a + 1, a + n + 1, [](int x, int y) { return x > y; });
  sort(b + 1, b + m + 1, [](int x, int y) { return x > y; });
  for (int i = 1; i <= n; i++)
    a[i] += a[i - 1];
  for (int i = 1; i <= m; i++)
    b[i] += b[i - 1];
  while (q--) {
    int xx, yy, zz;
    cin >> xx >> yy >> zz;
    if (!zz) {
      cout << 0 << '\n';
      continue;
    }
    int l = max(0, zz - yy), r = min(xx, zz);
    ll ans = 0;
    while (r - l > 2) {
      int m1 = l + (r - l) / 3, m2 = r - (r - l) / 3;
      if (a[m1] + b[zz - m1] < a[m2] + b[zz - m2])
        l = m1 + 1;
      else if (a[m1] + b[zz - m1] > a[m2] + b[zz - m2])
        r = m2 - 1;
      else
        l = m1, r = m2;
    }
    for (int i = l; i <= r; i++)
      ans = max(a[i] + b[zz - i], ans);
    cout << ans << '\n';
  }
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int _t;
  cin >> _t;
  while (_t--)
    solve();
  return 0;
}
