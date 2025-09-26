/*
 * Problem URL : https://codeforces.com/problemset/problem/2063/F1
 * Submit Date : 2025-08-23
 */

#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e6 + 5;
const int mod = 998244353;

int T, n, l, r, tot, ans;
int fac[N], inv[N], id[N], sz[N], s[N], C[N];

inline int mi(int a, int b = mod - 2) {
  int ans = 1;
  while (b) {
    if (b & 1)
      ans = ans * a % mod;
    a = a * a % mod;
    b >>= 1;
  }
  return ans;
}

inline int cat(int n) {
  return fac[n + n] * inv[n] % mod * inv[n] % mod * mi(n + 1) % mod;
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> T;
  fac[0] = inv[0] = 1;
  while (T--) {
    cin >> n;
    for (int i = 1; i <= n * 2; ++i) {
      fac[i] = fac[i - 1] * i % mod;
      inv[i] = inv[i - 1] * mi(i) % mod;
    }
    for (int i = 0; i <= n; ++i)
      C[i] = cat(i);
    tot = 1;
    cout << C[n] << " ";
    for (int i = 1; i <= n * 2; ++i)
      id[i] = 1;
    for (int i = 1; i <= n; ++i) {
      cin >> l >> r;
      tot++;
      for (int j = l + 1; j < r; ++j) {
        if (id[j] == id[l])
          id[j] = tot;
      }
      id[l] = id[r] = 0;
      for (int j = 1; j <= tot; ++j)
        s[j] = 0;
      for (int j = 1; j <= n * 2; ++j)
        s[id[j]]++;
      ans = 1;
      for (int j = 1; j <= tot; ++j)
        ans = ans * C[s[j] / 2] % mod;
      cout << ans << " ";
    }
    cout << "\n";
  }
  return 0;
}
