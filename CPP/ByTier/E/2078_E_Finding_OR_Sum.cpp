/*
 * Problem URL : https://codeforces.com/problemset/problem/2078/E
 * Submit Date : 2025-08-22
 */

#include <bits/stdc++.h>
#define int long long
using namespace std;
const int o = 1e6 + 3;
const int mod = 998244353;
int n, m, T, k, b[o], ans, a[o], d[o];
char c[o], l[o], r[o];
signed main() {
  ios::sync_with_stdio(0);
  cin >> T;
  int u = 0x2aaaaaaa, v = 0x15555555;
  while (T--) {
    int x = 0, y = 0, l, r;
    cout << u << "\n";
    cout.flush();
    cin >> l;
    cout << v << "\n";
    cout.flush();
    cin >> r;
    l -= (u << 1), r -= (v << 1);
    for (int i = 0; i < 30; i++) {
      int q;
      if (i & 1)
        q = r;
      else
        q = l;
      if (q & (1 << i))
        x |= (1 << i);
      else if (q & (1 << (i + 1)))
        x |= (1 << i), y |= (1 << i);
    }
    cout << "!" << "\n";
    cout.flush();
    cin >> m;
    cout << (m | x) + (m | y) << "\n";
  }
  return 0;
}