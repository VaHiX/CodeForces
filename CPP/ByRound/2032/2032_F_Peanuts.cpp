/*
 * Problem URL : https://codeforces.com/contest/2032/problem/F
 * Submit Date : 2025-09-09
 */

#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353;
const int N = 1e6;
int v[N];
int ps[N + 1];
int p[N + 1];
int f[4];
void solve() {
  f[0] = f[1] = f[2] = f[3] = 0;
  p[0] = 1;
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> v[i];
    ps[i + 1] = (ps[i] ^ v[i]);
    p[i + 1] = 1ll * p[i] * 2 % mod;
  }
  int nr = 0;
  while (nr < n && v[nr] == 1) {
    nr++;
  }
  if (nr == n) {
    cout << (n % 2 == 1 ? p[n - 1] : 0) << '\n';
    return;
  }
  int sum = 0;
  for (int i = nr; i < n; i++) {
    int x = min((ps[nr] ^ ps[i + 1]), 2);
    f[x] = (f[x] + p[max(n - i - 2, 0)]) % mod;
  }
  int sum2 = (((f[0] + f[1]) % mod + f[2]) % mod + f[3]) % mod;
  int ans = 0;
  for (int i = 0; i <= nr; i++) {
    int x = (ps[nr] ^ ps[i]);
    int nr = p[max(i - 1, 0)];
    if (i % 2 == 0) {
      /// a turn
      ans = (ans + 1ll * nr * (sum2 - f[x] + mod) % mod) % mod;
    } else {
      /// b turn
      ans = (ans + 1ll * nr * f[x] % mod) % mod;
    }
  }
  cout << ans << '\n';
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--)
    solve();
  return 0;
}
