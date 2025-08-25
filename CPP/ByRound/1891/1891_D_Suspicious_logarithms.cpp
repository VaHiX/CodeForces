/*
 * Problem URL : https://codeforces.com/problemset/problem/1891/D
 * Submit Date : 2025-08-13
 */

#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
const ll INF = 4e18, mod = (1e9) + 7;
vector<array<ll, 3>> v;
void add(ll l, ll r) {
  int b = __lg(l);
  ll x = 1, c = 0;
  while (x < l) {
    if (x >= INF / b)
      x = INF;
    else
      x *= b;
    c++;
  }
  if (r <= x)
    v.push_back({l, r, c - 1});
  else {
    if (l < x)
      v.push_back({l, x, c - 1});
    v.push_back({x, r, c});
  }
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  for (int m = 2; m <= 60; m++)
    add(1LL << m, 2LL << m);
  int q;
  cin >> q;
  while (q--) {
    ll l, r, res = 0;
    cin >> l >> r;
    r++;
    for (auto [L, R, val] : v) {
      ll a = max(L, l), b = min(r, R);
      if (a < b)
        res = (res + (b - a) % mod * val) % mod;
    }
    cout << res << "\n";
  }
  return 0;
}
