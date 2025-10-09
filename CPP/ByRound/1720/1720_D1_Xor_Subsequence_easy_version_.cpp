/*
 * Problem URL : https://codeforces.com/problemset/problem/1720/D1
 * Submit Date : 2025-08-13
 */

#include <bits/stdc++.h>
using namespace std;
const int N = 300100;
int f[N], a[N];
void solve() {
  int n;
  cin >> n;
  int ans = 0;
  for (int i = 0; i < n; i++)
    cin >> a[i];
  for (int i = 0; i < n; i++) {
    f[i] = 1;
    for (int j = (i >> 8 << 8); j < i; j++)
      if ((a[j] ^ i) < (a[i] ^ j))
        f[i] = max(f[i], f[j] + 1);
    ans = max(ans, f[i]);
  }
  cout << ans << '\n';
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)
    solve();
}