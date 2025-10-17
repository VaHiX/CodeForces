/*
 * Problem URL : https://codeforces.com/contest/2028/problem/C
 * Submit Date : 2025-09-09
 */

#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n, m, v;
    cin >> n >> m >> v;
    int a[n + 1] = {}, pre[n + 1] = {}, suf[n + 2] = {};
    for (int i = 1; i <= n; i++)
      cin >> a[i];
    for (int i = 1, c = 0, s = 0; i <= n; i++) {
      s += a[i];
      if (s >= v)
        c++, s = 0;
      pre[i] = c;
    }
    for (int i = n, c = 0, s = 0; i >= 1; i--) {
      s += a[i];
      if (s >= v)
        c++, s = 0;
      suf[i] = c;
    }
    if (pre[n] < m) {
      cout << "-1\n";
      continue;
    }
    ll sum = 0, res = 0;
    for (int r = 1, l = 1; r <= n; r++) {
      sum += a[r];
      while (l <= r && pre[l - 1] + suf[r + 1] < m)
        sum -= a[l++];
      res = max(res, sum);
    }
    cout << res << "\n";
  }
  return 0;
}
