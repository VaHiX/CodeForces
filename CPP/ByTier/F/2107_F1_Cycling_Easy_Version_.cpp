/*
 * Problem URL : https://codeforces.com/problemset/problem/2107/F1
 * Submit Date : 2025-08-17
 */

#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e3 + 5;
int T, n, a[N], b[N], s[N], ans;
void solve() {
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> a[i];
  b[n + 1] = 1e18;
  for (int i = n; i > 0; --i)
    b[i] = min(b[i + 1], a[i]);
  for (int i = 1; i <= n; ++i)
    s[i] = s[i - 1] + b[i] + (a[i] != b[i]);
  ans = s[n];
  for (int i = 1; i <= n; ++i)
    if (a[i] == b[i])
      ans = min(ans, s[i] + (n - i) * (a[i] + 1) + n - i);
  cout << ans << "\n";
}
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  for (cin >> T; T; T--)
    solve();
  return 0;
}