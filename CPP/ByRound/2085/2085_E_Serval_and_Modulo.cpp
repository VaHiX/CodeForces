/*
 * Problem URL : https://codeforces.com/problemset/problem/2085/E
 * Submit Date : 2025-08-22
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll N = 1e6 + 2;
ll a[N], b[N], c[N], sc[N], n, mxB;

bool chk(ll x) {
  if (x <= mxB || x > N)
    return 0;
  bool ok = 1;
  for (int i = 1; i <= n; ++i)
    if (--c[a[i] % x] < 0)
      ok = 0;
  for (int i = 1; i <= n; ++i)
    c[a[i] % x] = 0;
  for (int i = 1; i <= n; ++i)
    c[b[i]] = sc[b[i]];
  return ok;
}

void solve() {
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> a[i];
  for (int i = 1; i <= n; ++i)
    cin >> b[i];

  ll s = 0;
  for (int i = 1; i <= n; ++i)
    s += a[i] - b[i], ++c[b[i]];

  for (int i = 1; i <= n; ++i)
    sc[b[i]] = c[b[i]];

  mxB = *max_element(b + 1, b + n + 1);

  ll ans = -1;
  for (ll x = 1; x * x <= s; ++x) {
    if (s % x)
      continue;
    if (chk(x)) {
      ans = x;
      break;
    }
    if (chk(s / x)) {
      ans = s / x;
      break;
    }
  }

  assert(ans != 1 || !mxB);
  cout << (chk(N) ? N : ans) << '\n';

  for (int i = 1; i <= n; ++i)
    c[b[i]] = sc[b[i]] = 0;
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  ll T;
  cin >> T;
  while (T--)
    solve();
}