/*
 * Problem URL : https://codeforces.com/problemset/problem/2106/F
 * Submit Date : 2025-08-17
 */

#include <bits/stdc++.h>
using namespace std;
long long t, n, U, D, ans;
string s;
int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  for (cin >> t; t; t--) {
    cin >> n >> s;
    s = " " + s, ans = D = U = 0;
    for (int i = 1; i <= n; i++) {
      if (s[i] == '0') {
        D += n - i, U += i - 1;
      } else {
        U = D + 1, D = 0;
      }
      ans = max({ans, U, D});
    }
    cout << ans << '\n';
  }
  return 0;
}