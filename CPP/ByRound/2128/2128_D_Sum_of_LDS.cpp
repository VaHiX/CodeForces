/*
 * Problem URL : https://codeforces.com/problemset/problem/2128/D
 * Submit Date : 2025-08-14
 */

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int kMaxN = 5e5 + 100;

int t, n, a[kMaxN];
ll ans;

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  for (cin >> t; t--;) {
    cin >> n, ans = 0;
    for (int i = 1; i <= n; i++) {
      cin >> a[i], a[i - 1] > a[i] && (ans += (n - i + 1ll) * (i - 1));
    }
    cout << ans + (1ll + n) * n / 2 << '\n';
  }
  return 0;
}