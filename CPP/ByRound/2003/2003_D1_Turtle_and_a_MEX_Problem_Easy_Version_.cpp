/*
 * Problem URL : https://codeforces.com/contest/2003/problem/D1
 * Submit Date : 2025-09-14
 */

// 18:47
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
int n, a[N + 10], l, t, m, mx;
bool vis[N + 10];
void solve() {
  cin >> n >> m, mx = 0;
  bool op;
  for (int i = 1; i <= n; ++i) {
    cin >> l;
    for (int j = 1; j <= l; ++j)
      cin >> a[j], vis[min(a[j], N)] = true;
    op = false;
    for (int j = 0;; ++j) {
      if (!vis[j] && op) {
        mx = max(mx, j);
        break;
      }
      if (!vis[j])
        op = true;
    }
    for (int j = 1; j <= l; ++j)
      vis[min(a[j], N)] = false;
  }
  if (m <= mx)
    cout << mx * 1LL * m + mx << "\n";
  else
    cout << mx * 1LL * mx + (mx + 1 + m) * 1LL * (m - mx) / 2 + mx << "\n";
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> t;
  while (t--)
    solve();
  return 0;
}