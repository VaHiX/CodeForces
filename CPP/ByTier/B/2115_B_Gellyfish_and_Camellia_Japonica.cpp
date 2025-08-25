/*
 * Problem URL : https://codeforces.com/problemset/problem/2115/B
 * Submit Date : 2025-08-16
 */

#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 5;
int n, q, a[N], b[N], c[N];
int x[N], y[N], z[N];

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
      cin >> b[i];
      a[i] = b[i];
    }
    for (int i = 1; i <= q; i++)
      cin >> x[i] >> y[i] >> z[i];
    for (int i = q; i >= 1; i--) {
      a[x[i]] = max(a[x[i]], a[z[i]]);
      a[y[i]] = max(a[y[i]], a[z[i]]);
      if (y[i] != z[i] && x[i] != z[i])
        a[z[i]] = 0;
    }
    for (int i = 1; i <= n; i++)
      c[i] = a[i];
    for (int i = 1; i <= q; i++)
      a[z[i]] = min(a[x[i]], a[y[i]]);
    bool fg = 1;
    for (int i = 1; i <= n; i++)
      fg &= (a[i] == b[i]);
    if (!fg) {
      cout << -1 << endl;
    } else {
      for (int i = 1; i <= n; i++)
        cout << c[i] << ' ';
      cout << endl;
    }
  }
  return 0;
}