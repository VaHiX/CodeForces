/*
 * Problem URL : https://codeforces.com/problemset/problem/2075/C
 * Submit Date : 2025-08-16
 */

#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  int t;
  cin >> t;
  while (t--) {
    int n, m;
    cin >> n >> m;
    vector<int> v(n + 2);
    for (int i = 0; i < m; ++i) {
      int x;
      cin >> x;
      v[x]++;
    }
    for (int i = n; i; --i)
      v[i] += v[i + 1];
    int ans = 0;
    for (int i = 1; i <= n / 2; ++i) {
      ans += (v[n - i] * max(0LL, v[i] - 1) * ((i != n - i) + 1));
    }
    cout << ans << '\n';
  }
}
