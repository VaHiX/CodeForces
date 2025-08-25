/*
 * Problem URL : https://codeforces.com/problemset/problem/2086/D
 * Submit Date : 2025-08-22
 */

#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 5;
const int M = 27;
const int mod = 998244353;
#define int long long
int c[M], f[N], facny[N], fac[N];
int qpow(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1) {
      res = (res * a) % mod;
    }
    a = (a * a) % mod, b >>= 1;
  }
  return res;
}
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  fac[0] = facny[0] = 1;
  for (int i = 1; i < N; i++) {
    fac[i] = (fac[i - 1] * i) % mod;
  }
  facny[N - 1] = qpow(fac[N - 1], mod - 2);
  for (int i = N - 2; i >= 1; i--) {
    facny[i] = (facny[i + 1] * (i + 1)) % mod;
  }
  int T;
  cin >> T;
  while (T--) {
    int n = 0, ans = 1;
    for (int i = 1; i <= 26; i++) {
      cin >> c[i];
      n += c[i], ans = (ans * facny[c[i]]) % mod;
      ;
    }
    ans = (ans * fac[n / 2] % mod * fac[(n + 1) / 2]) % mod;
    for (int i = 1; i <= n / 2; i++)
      f[i] = 0;
    f[0] = 1;
    for (int i = 1; i <= 26; i++) {
      if (c[i] == 0) {
        continue;
      }
      for (int j = n / 2; j >= c[i]; j--) {
        f[j] += f[j - c[i]];
      }
    }
    cout << (ans * f[n / 2]) % mod << '\n';
  }
  return 0;
}