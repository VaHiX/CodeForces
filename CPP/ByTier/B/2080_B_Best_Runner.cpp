/*
 * Problem URL : https://codeforces.com/problemset/problem/2080/B
 * Submit Date : 2025-08-23
 */

#include <iostream>
using namespace std;
const int N = 300010;
int a[N], b[N];
int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int n, m, p, ans = 0;
  cin >> n >> m >> p;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  for (int i = 1; i <= m; i++)
    cin >> b[i];
  b[m + 1] = n + 1;
  for (int i = 1; i <= m; i++) {
    for (int j = b[i], tot = p, cnt = 0; j > b[i - 1] && tot >= 0; j--) {
      ans = max(ans, cnt + tot / a[j]);
      cnt++, tot -= a[j];
    }
    for (int j = b[i], tot = p, cnt = 0; j < b[i + 1] && tot >= 0; j++) {
      ans = max(ans, cnt + tot / a[j]);
      cnt++, tot -= a[j];
    }
  }
  cout << ans;
}
