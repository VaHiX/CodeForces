/*
 * Problem URL : https://codeforces.com/contest/2025/problem/E
 * Submit Date : 2025-09-10
 */

#include <bits/stdc++.h>
#define mod 998244353
using namespace std;
const int N = 510;
int n, m, fc[N], f[N], g[N][N];
int ksm(int a, int b) {
  int tmp = 1;
  while (b) {
    if (b & 1)
      tmp = 1ll * tmp * a % mod;
    a = 1ll * a * a % mod;
    b >>= 1;
  }
  return tmp;
}
int c(int n, int m) {
  return 1ll * fc[n] * ksm(fc[m], mod - 2) % mod * ksm(fc[n - m], mod - 2) %
         mod;
}
int main() {
  cin >> n >> m;
  fc[0] = 1;
  for (int i = 1; i <= m; i++)
    fc[i] = 1ll * fc[i - 1] * i % mod;
  for (int i = 0; i <= m; i += 2)
    f[i] = (c(m, (m + i) / 2) - c(m, (m + i) / 2 + 1) + mod) % mod;
  g[1][0] = 1;
  for (int i = 2; i <= n; i++)
    for (int j = 0; j <= m; j += 2)
      for (int k = 0; k <= j; k += 2)
        g[i][j] = (g[i][j] + 1ll * g[i - 1][j - k] * f[k] % mod) % mod;
  int ans = 0;
  for (int i = 0; i <= m; i += 2) {
    ans = (1ll * g[n][i] * f[i] % mod + ans) % mod;
  }
  cout << ans;
  return 0;
}