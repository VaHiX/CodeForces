/*
 * Problem URL : https://codeforces.com/problemset/problem/2132/C1
 * Submit Date : 2025-08-21
 */

#include <bits/stdc++.h>
using namespace std;
#define int long long
int T;
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> T;
  while (T--) {
    int n, ans = 0, i = 0, s = 1;
    cin >> n;
    while (n) {
      ans += n % 3 * (s * 3 + s / 3 * i);
      n /= 3;
      i++;
      s *= 3;
    }
    cout << ans << "\n";
  }
  return 0;
} // rp++