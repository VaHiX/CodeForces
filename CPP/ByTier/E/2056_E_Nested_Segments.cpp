/*
 * Problem URL : https://codeforces.com/problemset/problem/2056/E
 * Submit Date : 2025-08-24
 */

#include <algorithm>
#include <cstdio>
#include <iostream>
#define mod 998244353
using namespace std;
int n = 200000, m, ans;
int inv[400005], fac[400005], invfac[400005];
int f[200005], stk[200005], top;
struct seg {
  int l, r;
} s[200005];
bool operator<(seg x, seg y) {
  if (x.r == y.r)
    return x.l > y.l;
  return x.r < y.r;
}
inline int sub(int x, int y) {
  if ((x -= y) < 0)
    x += mod;
  return x;
}
inline int C(int x, int y) {
  return 1ll * fac[x] * invfac[y] % mod * invfac[x - y] % mod;
}
void init() {
  fac[0] = invfac[0] = inv[1] = fac[1] = invfac[1] = f[1] = 1;
  for (int i = 2; i <= 2 * n; i += 1) {
    inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod;
    fac[i] = 1ll * fac[i - 1] * i % mod;
    invfac[i] = 1ll * invfac[i - 1] * inv[i] % mod;
  }
  for (int i = 1; i < n; i += 1) {
    f[i + 1] = sub(C(2 * i, i), C(2 * i, i - 1));
  }
  return;
}
void solve() {
  scanf("%d%d", &m, &n);
  ans = 1;
  for (int i = 1; i <= n; i += 1) {
    scanf("%d%d", &s[i].l, &s[i].r);
  }
  sort(s + 1, s + n + 1);
  top = 0;
  if (s[n].l != 1 || s[n].r != m)
    s[++n] = (seg){1, m};
  for (int i = 1, j; i <= n; i += 1) {
    int len = s[i].r - s[i].l + 1;
    while (top) {
      j = stk[top];
      if (s[i].l <= s[j].l) {
        len -= (s[j].r - s[j].l);
        top -= 1;
      } else
        break;
    }
    ans = 1ll * ans * f[len] % mod;
    stk[++top] = i;
  }
  printf("%d\n", ans);
  return;
}
int main() {
  init();
  int t;
  scanf("%d", &t);
  while (t--)
    solve();
  return 0;
}
