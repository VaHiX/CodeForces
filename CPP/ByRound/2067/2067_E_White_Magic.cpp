/*
 * Problem URL : https://codeforces.com/problemset/problem/2067/E
 * Submit Date : 2025-08-23
 */

#include <bits/stdc++.h>
using namespace std;
#define int long long
int a[200005], cnt[200005];
void DO() {
  int n;
  cin >> n;

  int tk = n, c = 0, cc;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    c += a[i] == 0, cc = c;
  }

  for (int i = n, mex = 0; i >= 1; i--) {
    if (a[i] < mex)
      tk--;
    if (a[i] <= n and (a[i] != 0 or c == 1))
      cnt[a[i]]++;
    c -= a[i] == 0;
    while (cnt[mex])
      mex++;
  }
  cout << n - cc + (tk == n and cc) << '\n';
  for (int i = 0; i <= n; i++)
    cnt[i] = 0;
}
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t, i = 1;
  cin >> t;
  while (t--) {
    DO();
  }
}