/*
 * Problem URL : https://codeforces.com/problemset/submit
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 2;
int T, n, m, c, a[N], b[N];
int main() {
  cin.tie(0)->sync_with_stdio(0);
  for (cin >> T; T--;) {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
      cin >> a[i];
    c = a[1];
    sort(a + 1, a + n + 1);
    for (int i = 1, x; i <= m; ++i) {
      cin >> x;
      if (x <= c || x > a[n])
        b[i] = 0;
      else
        b[i] = a + n + 1 - lower_bound(a + 1, a + n + 1, x);
    }
    sort(b + 1, b + m + 1);
    for (int i = 1; i <= m; ++i) {
      long long ans = m / i;
      for (int j = i; j <= m; j += i)
        ans += b[j];
      cout << ans << " \n"[i == m];
    }
  }
  return 0;
}
