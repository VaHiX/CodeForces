/*
 * Problem URL : https://codeforces.com/contest/2034/problem/F2
 * Submit Date : 2025-09-07
 */

#include <bits/stdc++.h>
using namespace std;
const int N = 5010, M = 4e5 + 10, mod = 998244353;
struct node {
  int x, y;
  int operator<(const node &a) const { return x + y < a.x + a.y; };
} a[N];
int fac[M], inv[M], w[N];
int qpow(int a, int b) {
  int ans = 1;
  while (b) {
    if (b & 1)
      ans = 1ll * ans * a % mod;
    a = 1ll * a * a % mod;
    b >>= 1;
  }
  return ans;
}
void pre(int n) {
  fac[0] = 1;
  for (int i = 1; i <= n; i++)
    fac[i] = 1ll * i * fac[i - 1] % mod;
  inv[n] = qpow(fac[n], mod - 2);
  for (int i = n; i >= 1; i--)
    inv[i - 1] = 1ll * i * inv[i] % mod;
}
int C(int n, int m) { return 1ll * fac[n] * inv[m] % mod * inv[n - m] % mod; }
void solve() {
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 1; i <= k; i++) {
    scanf("%d%d", &a[i].x, &a[i].y);
    a[i].x = n - a[i].x;
    a[i].y = m - a[i].y;
  }
  a[0].x = a[0].y = 0;
  a[k + 1].x = n;
  a[k + 1].y = m;
  sort(a + 1, a + k + 1);
  w[k + 1] = 1;
  for (int i = k; i >= 1; i--) {
    w[i] = 0;
    for (int j = i + 1; j <= k + 1; j++) {
      if (a[i].x <= a[j].x && a[i].y <= a[j].y) {
        int X = a[j].x - a[i].x, Y = a[j].y - a[i].y;
        w[i] = (w[i] + 1ll * w[j] * C(X + Y, X)) % mod;
      }
    }
  }
  int ans = 0;
  for (int i = 1; i <= k + 1; i++) {
    int t = 2 * a[i].x + a[i].y;
    ans = (ans + 1ll * t * C(a[i].x + a[i].y, a[i].x) % mod * w[i]) % mod;
  }
  ans = 1ll * ans * fac[n] % mod * fac[m] % mod * inv[n + m] % mod;
  printf("%d\n", ans);
}
int main() {
  int T;
  pre(4e5);
  scanf("%d", &T);
  while (T--) {
    solve();
  }
  return 0;
}