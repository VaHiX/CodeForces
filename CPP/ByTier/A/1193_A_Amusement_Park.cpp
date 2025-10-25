/*
 * Problem URL : https://codeforces.com/contest/1193/problem/A
 * Submit Date : 2025-09-02
 */

#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353;
int n, m, f[1 << 18], u[400], v[400];
bool can[1 << 18];
signed main() {
  cin >> n >> m;
  for (int i = 1; i <= m; i++)
    cin >> u[i] >> v[i], --u[i], --v[i];
  f[0] = 1;
  for (int i = 1; i < (1 << n); i++) {
    can[i] = 1;
    for (int j = 1; j <= m; j++) {
      if ((i >> u[j] & 1) && (i >> v[j] & 1))
        can[i] = 0;
    }
  }
  for (int i = 1; i < (1 << n); i++) {
    for (int j = i; j; j = (j - 1) & i) {
      if (can[j])
        f[i] = ((f[i] + (__builtin_popcount(j) & 1 ? 1 : -1) * f[i ^ j]) % mod +
                mod) %
               mod;
    }
  }
  cout << 1ll * 499122177 * f[(1 << n) - 1] % mod * m % mod << endl;
}