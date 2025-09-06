/*
 * Problem URL : https://codeforces.com/problemset/problem/2051/D
 * Submit Date : 2025-08-16
 */

#include <bits/stdc++.h>
using namespace std;
long long T, n, x, y, a[200005], h, t, s, ans;
int main() {
  for (cin >> T; T--; ans = 0, s = 0) {
    cin >> n >> x >> y;
    for (int i = 1; i <= n; i++)
      scanf("%d", &a[i]), s += a[i];
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++) {
      int h = lower_bound(a + 1 + i, a + 1 + n, s - a[i] - y) - a;
      int t = upper_bound(a + 1 + i, a + 1 + n, s - a[i] - x) - a;
      ans += t - h;
    }
    cout << ans << endl;
  }
  return 0;
}