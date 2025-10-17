/*
 * Problem URL : https://codeforces.com/problemset/problem/2072/E
 * Submit Date : 2025-08-22
 */

#include <bits/stdc++.h>
using namespace std;
int t, n, cnt, _, x_, x[1000], y[1000];
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n;
    cnt = _ = x_ = 0;
    while (n) {
      if (_ > n)
        _ = 0, x_++;
      cnt++;
      x[cnt] = x_, y[cnt] = cnt;
      n -= _;
      _++;
    }
    cout << cnt << '\n';
    for (int i = 1; i <= cnt; i++)
      cout << x[i] << ' ' << y[i] << '\n';
  }
  return 0;
}
