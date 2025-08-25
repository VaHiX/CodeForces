/*
 * Problem URL : https://codeforces.com/problemset/problem/2122/G
 * Submit Date : 2025-08-14
 */

#include <bits/stdc++.h>

#define N 200005
#define mod 998244353

typedef long long ll;

using namespace std;

ll ft[N], ftv[N], inv[N];

ll C(int n, int m) { return ft[n] * ftv[m] % mod * ftv[n - m] % mod; }
ll qpow(ll a, int b) {
  ll ans = 1;
  while (b) {
    if (b & 1)
      ans = ans * a % mod;
    a = a * a % mod;
    b >>= 1;
  }
  return ans;
}

int main() {
  ll ans;
  int i, k, T, n;
  scanf("%d", &T);
  ft[0] = ftv[0] = 1;
  for (i = 1; i < N; ++i) {
    if (i == 1)
      inv[i] = 1;
    else
      inv[i] = (mod - mod / i) * inv[mod % i] % mod;
    ftv[i] = ftv[i - 1] * inv[i] % mod;
    ft[i] = ft[i - 1] * i % mod;
  }
  while (T--) {

    scanf("%d %d", &n, &k);
    ans = 0;
    --n;
    --k;
    for (i = 0; i <= n - k; ++i) {
      if ((n + k + i) & 1)
        (ans -= qpow(i, n) * C(n + 1, i + k + 1)) %= mod;
      else
        (ans += qpow(i, n) * C(n + 1, i + k + 1)) %= mod;
    }
    ++n;
    ++k;
    for (i = 1; i <= n * 2 - 1; ++i)
      ans = ans * i % mod;
    for (i = 1; i <= n - 1; ++i)
      ans = ans * ((mod + 1) / 2) % mod;
    printf("%lld\n", (ans + mod) % mod);
  }
  return 0;
}
