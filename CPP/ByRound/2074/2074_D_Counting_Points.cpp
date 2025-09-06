/*
 * Problem URL : https://codeforces.com/problemset/problem/2074/D
 * Submit Date : 2025-08-22
 */

#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll t, n, m, x[200010], r[200010];
int main() {
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
      cin >> x[i];
    for (int i = 1; i <= n; i++)
      cin >> r[i];
    map<ll, ll> m;
    for (ll i = 1; i <= n; i++) {
      for (ll j = x[i] - r[i]; j <= x[i] + r[i]; j++) {
        ll now = floor(sqrt(r[i] * r[i] - (x[i] - j) * (x[i] - j))) * 2 + 1;
        m[j] = max(m[j], now);
      }
    }
    ll ans = 0;
    for (const auto &i : m) {
      ans += i.second;
    }
    cout << ans << endl;
  }
}