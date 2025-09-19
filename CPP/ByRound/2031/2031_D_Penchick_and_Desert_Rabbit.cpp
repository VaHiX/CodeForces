/*
 * Problem URL : https://codeforces.com/contest/2031/problem/D
 * Submit Date : 2025-09-09
 */

#include <bits/stdc++.h>
using namespace std;
int t, n, a[500005], mx[500005], mn[500005], f[500005];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++)
      cin >> a[i];
    mx[1] = a[1], mn[n] = a[n];
    for (int i = 2; i <= n; i++)
      mx[i] = max(mx[i - 1], a[i]);
    for (int i = n - 1; i >= 1; i--)
      mn[i] = min(mn[i + 1], a[i]);
    f[n] = mx[n];
    for (int i = n - 1; i >= 1; i--) {
      if (mx[i] <= mn[i + 1])
        f[i] = mx[i];
      else
        f[i] = f[i + 1];
    }
    for (int i = 1; i <= n; i++)
      cout << f[i] << " ";
    cout << "\n";
  }
  return 0;
}
