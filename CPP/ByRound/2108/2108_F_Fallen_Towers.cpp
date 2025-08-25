/*
 * Problem URL : https://codeforces.com/problemset/problem/2108/F
 * Submit Date : 2025-08-17
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll N = 1e5 + 2;
ll a[N], b[N], od[N], n;

bool chk(ll x) {
  b[n] = x - 1, od[n] = 0;
  for (int i = n - 1; i >= 1; --i)
    b[i] = max(0ll, b[i + 1] - 1), od[i] = 0;
  ll cur = 0;
  for (int i = 1; i <= n; ++i) {
    cur -= od[i] - (i > 1);
    if (cur < b[i])
      return 0;
    ll x = cur + a[i] - b[i];
    ++od[1 + min(n, i + x)];
  }
  return 1;
}

void solve() {
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> a[i];

  ll l = 1, r = n, ans = l;
  while (l <= r) {
    ll m = (l + r) / 2;
    if (chk(m)) {
      l = m + 1;
      ans = m;
    } else
      r = m - 1;
  }

  cout << ans << '\n';
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  ll T;
  cin >> T;
  while (T--)
    solve();
}