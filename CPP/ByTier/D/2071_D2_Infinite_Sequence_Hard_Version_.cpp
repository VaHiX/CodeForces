/*
 * Problem URL : https://codeforces.com/problemset/problem/2071/D2
 * Submit Date : 2025-08-22
 */

#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 10;
int n, l, r, a[N << 1], b[N << 1], s[N << 1], ans;
int solve(int r) {
  if (r <= n * 2 + 1)
    return s[r];
  int t = r - n * 2 - 1;
  int rr = n + t / 4 * 2 + min(t % 4, 2ll);
  int ss = solve(rr) - s[n];
  if (!b[n])
    return s[n * 2 + 1] + ss;
  return s[n * 2 + 1] + t - ss;
}
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int T;
  cin >> T;
  while (T--) {
    cin >> n >> l >> r;
    for (int i = 1; i <= n; ++i) {
      cin >> a[i];
      b[i] = b[i - 1] ^ a[i];
      s[i] = s[i - 1] + a[i];
    }
    if (n % 2 == 0) {
      ++n;
      a[n] = b[n / 2];
      b[n] = b[n - 1] ^ a[n];
      s[n] = s[n - 1] + a[n];
    }
    for (int i = n + 1; i <= n * 2 + 1; ++i) {
      a[i] = b[i / 2];
      b[i] = b[i - 1] ^ a[i];
      s[i] = s[i - 1] + a[i];
    }
    cout << solve(r) - solve(l - 1) << '\n';
  }
  return 0;
}