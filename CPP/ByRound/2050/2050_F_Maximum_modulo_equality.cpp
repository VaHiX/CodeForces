/*
 * Problem URL : https://codeforces.com/problemset/submit
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>
using namespace std;
int T, n, q, a[200200], b[200200], st[20][200200];
void f() {
  for (int i = 1, k = 1; i <= 20 && k <= n; i++, k <<= 1) {
    for (int j = 1; j + k <= n; j++) {
      st[i][j] = __gcd(st[i - 1][j], st[i - 1][j + k]);
    }
  }
}
int g(int l, int r) {
  int d = __lg(r - l + 1), k = 1 << d;
  return __gcd(st[d][l], st[d][r - k + 1]);
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> T;
  while (T--) {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      b[i] = abs(a[i] - a[i - 1]);
      st[0][i] = b[i];
    }
    f();
    while (q--) {
      int l, r;
      cin >> l >> r;
      if (l == r) {
        cout << "0 ";
        continue;
      }
      l++;
      int gg = g(l, r);
      cout << gg << " ";
    }
    cout << "\n";
  }
  return 0;
}