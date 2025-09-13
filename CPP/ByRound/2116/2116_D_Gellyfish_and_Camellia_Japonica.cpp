/*
 * Problem URL : https://codeforces.com/problemset/problem/2116/D
 * Submit Date : 2025-08-16
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int T = 1;
  cin >> T;
  while (T--) {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++) {
      cin >> a[i], b[i] = a[i];
    }
    vector<int> x(q + 1), y(q + 1), z(q + 1);
    for (int i = 1; i <= q; i++) {
      cin >> x[i] >> y[i] >> z[i];
    }
    for (int i = q; i >= 1; i--) {
      a[x[i]] = max(a[x[i]], a[z[i]]);
      a[y[i]] = max(a[y[i]], a[z[i]]);
      if (x[i] != z[i] && y[i] != z[i])
        a[z[i]] = 0;
    }
    vector<int> c(n + 1);
    for (int i = 1; i <= n; i++)
      c[i] = a[i];
    for (int i = 1; i <= q; i++) {
      a[z[i]] = min(a[x[i]], a[y[i]]);
    }
    bool fl = true;
    for (int i = 1; i <= n; i++)
      fl = fl && (a[i] == b[i]);
    if (!fl)
      cout << -1;
    else
      for (int i = 1; i <= n; i++)
        cout << c[i] << " ";
    cout << "\n";
  }
  return 0;
}
