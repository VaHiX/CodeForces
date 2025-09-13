/*
 * Problem URL : https://codeforces.com/problemset/problem/2093/F
 * Submit Date : 2025-08-21
 */

#include <bits/stdc++.h>
using namespace std;
#define int long long
string a[508];
int n, m;
bool p[508];
void solve() {
  int mx = 0;
  cin >> n >> m;
  for (int i = 1; i <= n; i++)
    cin >> a[i], p[i] = false;
  for (int i = 1; i <= m; i++) {
    int sum = 0;
    for (int j = 1; j <= n; j++) {
      string tmp;
      cin >> tmp;
      if (tmp == a[j]) {
        sum++;
        p[j] = true;
      }
    }
    mx = max(mx, sum);
  }
  for (int i = 1; i <= n; i++) {
    if (p[i] == false)
      return void(cout << -1 << '\n');
  }
  int ans = mx + (n - mx) * 3;
  cout << ans << '\n';
}
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t--)
    solve();
  return 0;
}