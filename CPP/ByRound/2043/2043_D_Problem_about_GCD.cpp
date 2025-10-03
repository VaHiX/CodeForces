/*
 * Problem URL : https://codeforces.com/contest/2043/problem/D
 * Submit Date : 2025-08-25
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll l, r, G;

void solve() {
  cin >> l >> r >> G;
  ll lb = (l + G - 1) / G, ub = r / G;
  for (ll i = ub - lb; i >= 0; --i) {
    for (ll x = lb; x + i <= ub; ++x) {
      if (gcd(x, x + i) == 1) {
        cout << x * G << ' ' << (x + i) * G << '\n';
        return;
      }
    }
  }
  cout << "-1 -1\n";
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int t;
  cin >> t;
  while (t--)
    solve();
}
