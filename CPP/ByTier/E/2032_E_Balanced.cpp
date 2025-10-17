/*
 * Problem URL : https://codeforces.com/contest/2032/problem/E
 * Submit Date : 2025-09-09
 */

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define N 208555
int a[N], ans[N], n, i, T, ans2[N];
signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cout.tie(0);
  cin >> T;
  while (T--) {
    cin >> n;
    for (i = 1; i <= n; i++)
      cin >> a[i];
    for (i = 1; i <= n; i++) {
      ans[i + 1] += 1000000 - a[i];
      if (i >= 3)
        ans[(i & 1) ? 1 : 2] += 1000000 - a[i], ans[i] -= 1000000 - a[i];
    }
    for (i = 3; i <= n; i++)
      ans[i] += ans[i - 2];
    for (i = 1; i <= n; i++) {
      int x = ans[i];
      ans2[i + 2] += x;
      if (i >= 2)
        ans2[(i & 1) ? 2 : 1] += x, ans2[i + 1] -= x;
    }
    for (i = 3; i <= n; i++)
      ans2[i] += ans2[i - 2];
    for (i = 1; i <= n; i++)
      cout << ans2[i] << " ";
    cout << "\n";
    for (i = 0; i <= n + 10; i++)
      a[i] = ans[i] = ans2[i] = 0;
  }
  return 0;
}