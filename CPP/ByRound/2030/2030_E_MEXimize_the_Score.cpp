/*
 * Problem URL : https://codeforces.com/contest/2030/problem/E
 * Submit Date : 2025-09-09
 */

#include <algorithm>
#include <cstdio>
#include <iostream>
using std::cin;
using std::cout;
constexpr int N = 200005, p = 998244353;
int t, n, a, b[N], fac[N], inv[N], g[N], f[N], s[N], k[N], ans, sum;
inline int qpow(int a, int b, int p, int t = 1) {
  for (; b; b >>= 1, a = 1ll * a * a % p)
    if (b & 1)
      t = 1ll * t * a % p;
  return t;
}
inline int C(int n, int m, int p) {
  if (n < 0 || m < 0 || n < m)
    return 0;
  return 1ll * fac[n] * inv[m] % p * inv[n - m] % p;
}
signed main() {
  //	freopen(".in","r",stdin);
  //	freopen(".out","w",stdout);
  std::ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  fac[0] = g[0] = 1;
  for (int i = 1; i < N; ++i) {
    fac[i] = 1ll * fac[i - 1] * i % p;
    g[i] = (g[i - 1] << 1) % p;
  }
  inv[N - 1] = qpow(fac[N - 1], p - 2, p);
  for (int i = N - 2; i >= 0; --i)
    inv[i] = inv[i + 1] * (i + 1ll) % p;
  for (cin >> t; t--; cout << ans << '\n') {
    cin >> n;
    for (int i = 0; i < n; ++i)
      b[i] = 0;
    for (int i = 1; i <= n; ++i) {
      cin >> a;
      ++b[a];
    }
    ans = 0;
    sum = n - b[0];
    for (int i = b[0]; i >= 1; --i) {
      f[i] = C(b[0], i, p);
      s[i] = (f[i] + s[i + 1]) % p;
      ans = (ans + 1ll * f[i] * g[sum] % p * i % p) % p;
    }
    for (int i = 1; i < n; ++i) {
      sum -= b[i];
      if (!b[i])
        break;
      int sc = 0;
      for (int j = b[i]; j >= 1; --j) {
        sc = (sc + 1ll * C(b[i], j, p)) % p;
        k[j] = (1ll * s[j + 1] * C(b[i], j, p) % p + 1ll * f[j] * sc % p) % p;
      }
      for (int j = 1; j <= b[i - 1]; ++j)
        s[j] = f[j] = 0;
      for (int j = b[i]; j >= 1; --j) {
        f[j] = k[j];
        ans = (ans + 1ll * f[j] * g[sum] % p * j % p) % p;
        s[j] = (s[j + 1] + f[j]) % p;
      }
    }
    for (int i = 1; i <= n; ++i)
      s[i] = f[i] = 0;
  }
  return 0;
} // 第一百七回 散余资贾母明大义 复世职政老沐天恩