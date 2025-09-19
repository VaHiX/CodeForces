/*
 * Problem URL : https://codeforces.com/contest/1866/problem/M
 * Submit Date : 2025-09-07
 */

#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod = 998244353, N = 200005;
int qpow(int x, int y) {
  return y ? qpow(x * x % mod, y >> 1) * (y & 1 ? x : 1) % mod : 1;
}
int n, p[N], f[N], pp[N], sum[N];
signed main() {
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> p[i];
  for (int i = 0; i <= 99; i++)
    pp[i] = i * qpow(100, mod - 2) % mod;
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    f[i] = sum[p[i]] * pp[p[i]] % mod;
    f[i]++, (f[i] *= qpow((mod + 1 - pp[p[i]]) % mod, mod - 2)) %= mod;
    ans += f[i];
    for (int j = 0; j < 100; j++)
      sum[j] = (sum[j] + f[i]) * pp[j] % mod;
  }
  cout << ans % mod;
  return 0;
}
