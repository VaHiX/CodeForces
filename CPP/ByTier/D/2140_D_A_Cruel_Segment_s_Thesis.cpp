/*
 * Problem URL : https://codeforces.com/contest/2140/problem/D
 * Submit Date : 2025-09-09
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
  int n;
  cin >> n;
  vector<array<int, 2>> a(n), b(n);

  ll h = 0, ans = -1e18;
  for (int i = 0; i < n; i++) {
    cin >> a[i][0] >> a[i][1];
    h += a[i][1];
    b[i][0] = -a[i][0] - a[i][1], b[i][1] = a[i][1];
  }

  sort(b.begin(), b.end(), greater<array<int, 2>>());
  for (int i = 0; i < n / 2; i++)
    h += b[i][0];

  if (n % 2 == 0)
    ans = h;
  else
    for (int i = 0; i < n; i++) {
      if (i < n / 2)
        ans = max(ans, h - b[i][1] - b[i][0] + b[n / 2][0]);
      else
        ans = max(ans, h - b[i][1]);
    }

  for (int i = 0; i < n; i++)
    ans += a[i][1] - a[i][0];
  cout << ans << endl;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int nc;
  cin >> nc;
  while (nc--)
    solve();
  return 0;
}