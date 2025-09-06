/*
 * Problem URL : https://codeforces.com/problemset/problem/2093/D
 * Submit Date : 2025-08-21
 */

#include <iostream>
using namespace std;
void solve() {
  int n, q;
  cin >> n >> q;
  while (q--) {
    string s;
    cin >> s;
    if (s[0] == '-') {
      int x, y;
      cin >> x >> y;
      long long ans = 0;
      int m = n;
      int ad = 1 << (n - 1);
      while (m--) {
        ans <<= 2;
        if (x > ad && y > ad)
          x -= ad, y -= ad, ans += 1;
        if (x > ad && y <= ad)
          x -= ad, ans += 2;
        if (x <= ad && y > ad)
          y -= ad, ans += 3;
        ad >>= 1;
      }
      ans++;
      cout << ans << '\n';
    } else {
      long long d;
      cin >> d;
      d--;
      int x = 1, y = 1;
      int ad = 1;
      while (d) {
        int now = d & 3;
        if (now == 1)
          y += ad, x += ad;
        if (now == 2)
          x += ad;
        if (now == 3)
          y += ad;
        d >>= 2;
        ad <<= 1;
      }
      cout << x << ' ' << y << '\n';
    }
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}