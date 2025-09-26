/*
 * Problem URL : https://codeforces.com/problemset/problem/2092/E
 * Submit Date : 2025-08-22
 */

/*
 * Problem URL : https://codeforces.com/problemset/problem/2092/E
 * Submit Date : 2025-08-22
 */

#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
const int iv = 5e8 + 4;
using ll = long long;
ll qp(ll x, ll y, ll z = 1) {
  while (y) {
    if (y & 1)
      z = x * z % mod;
    x = x * x % mod;
    y >>= 1;
  }
  return z;
}
ll _, n, m, k, x, y, c, z, w, s;
inline int chk(ll x, ll y) {
  if (x == 1 || x == n)
    return y != 1 && y != m;
  return y == 1 || y == m;
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> _;
  while (_--) {
    cin >> n >> m >> k;
    w = 1;
    z = 2 * (n + m - 4);
    s = n * m - k;
    while (k--) {
      cin >> x >> y >> c;
      if (chk(x, y)) {
        z--;
        if (c)
          w ^= 1;
      }
    }
    if (!z)
      cout << w * qp(2, s) << '\n';
    else
      cout << qp(2, s - 1) << '\n';
  }
  return 0;
}