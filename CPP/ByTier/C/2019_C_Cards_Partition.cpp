/*
 * Problem URL : https://codeforces.com/contest/2019/problem/C
 * Submit Date : 2025-09-11
 */


#include <bits/stdc++.h>
using namespace std;
#define int long long
int T, n, m, sum, mx, ans, a[200005];
void solve() {
  cin >> n >> m, mx = sum = ans = 0;
  for (int i = 1; i <= n; i++)
    cin >> a[i], sum += a[i], mx = max(mx, a[i]);
  for (int i = 1; i <= n; i++)
    if ((sum + m) / i * i >= sum && (sum + m) / i >= mx)
      ans = i;
  cout << ans << '\n';
}
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  cin >> T;
  while (T--)
    solve();
  return 0;
}