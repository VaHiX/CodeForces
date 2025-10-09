/*
 * Problem URL : https://codeforces.com/problemset/problem/2053/I1
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long LL;
const int MAXN = 3e6 + 5;
int T, n, a[MAXN];
signed main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> T;
  while (T--) {
    cin >> n;
    LL sum = 0, L = 0, R = 0;
    int ans = n;
    for (int i = 1; i <= n; ++i)
      cin >> a[i], sum += a[i];
    for (int i = 1; i <= n; ++i) {
      L = max(0ll, L + a[i]), R = min(R + a[i], sum);
      if (L > R)
        ++ans, L = max(0, a[i]), R = sum + min(0, a[i]);
    }
    if (R != sum)
      ++ans;
    cout << ans << endl;
  }
  return 0;
}