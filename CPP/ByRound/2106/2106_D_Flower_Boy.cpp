/*
 * Problem URL : https://codeforces.com/problemset/problem/2106/D
 * Submit Date : 2025-08-17
 */

#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int t, n, m, ans;
int a[N], b[N];
int l[N], r[N];
void sovle() {
  cin >> n >> m;
  ans = 2e9;
  for (int i = 1; i <= m; i++)
    l[i] = 1e9, r[i] = 0;
  l[0] = 0, r[m + 1] = 1e9;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  for (int i = 1; i <= m; i++)
    cin >> b[i];
  for (int i = 1, j = 1; i <= n && j <= m; i++)
    if (a[i] >= b[j])
      l[j] = i, j++;
  for (int i = n, j = m; i >= 1 && j >= 1; i--)
    if (a[i] >= b[j])
      r[j] = i, j--;
  if (l[m] != 1e9 || r[1] != 0) {
    cout << 0 << "\n";
    return;
  }
  for (int i = 1; i <= m; i++) {
    if (l[i - 1] < r[i + 1])
      ans = min(ans, b[i]);
  }
  if (ans != 2e9)
    cout << ans << "\n";
  else
    cout << -1 << "\n";
  return;
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> t;
  while (t--) {
    sovle();
  }
  return 0;
}