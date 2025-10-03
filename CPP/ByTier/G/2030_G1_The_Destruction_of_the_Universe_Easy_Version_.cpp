/*
 * Problem URL : https://codeforces.com/contest/2030/problem/G1
 * Submit Date : 2025-09-09
 */

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define per(i, a, b) for (int i = (a); i >= (b); i--)
using namespace std;
using tup = tuple<int, int, int>;
const int N = 200005, P = 998244353;
int n, l[N], r[N], fac[N], inv[N], pr[N], su[N], f[N], g[N], f2[N];
tup p[2 * N];
void Inc(int &x, int y) {
  if ((x += y) >= P)
    x -= P;
}
void Dec(int &x, int y) {
  if ((x -= y) < 0)
    x += P;
}
int bp(int x, int y) {
  int r = 1;
  for (; y; y = y >> 1, x = 1ll * x * x % P)
    if (y & 1)
      r = 1ll * r * x % P;
  return r;
}
int C(int x, int y) {
  if (x < y)
    return 0;
  return 1ll * fac[x] * inv[y] % P * inv[x - y] % P;
}
void solve() {
  scanf("%d", &n), fac[0] = inv[0] = 1;
  rep(i, 1, n) fac[i] = 1ll * fac[i - 1] * i % P, inv[i] = bp(fac[i], P - 2);
  f2[0] = 1;
  rep(i, 1, n) f2[i] = 2ll * f2[i - 1] % P;
  int m = 0;
  rep(i, 1, n) scanf("%d%d", &l[i], &r[i]), p[++m] = {l[i], 0, i},
                                            p[++m] = {r[i], 1, i};
  sort(p + 1, p + m + 1);
  pr[0] = f[0] = 0;
  rep(i, 1, m) {
    pr[i] = pr[i - 1], f[i] = f[i - 1];
    if (get<1>(p[i]) == 1) {
      Inc(pr[i], 1);
      Inc(f[i], get<0>(p[i]));
    }
  }
  su[m + 1] = g[m + 1] = 0;
  per(i, m, 1) {
    su[i] = su[i + 1], g[i] = g[i + 1];
    if (get<1>(p[i]) == 0) {
      Inc(su[i], 1);
      Inc(g[i], get<0>(p[i]));
    }
  }
  int as = 0;
  rep(i, 1, m - 1) {
    int c1 = pr[i], c2 = su[i + 1], x, y, z;
    tie(x, y, z) = p[i];
    if (y == 0) {
      int tp = 0;
      Inc(tp, 1ll * g[i + 1] * C(c1 + c2 - 1, c2) % P);
      Dec(tp, 1ll * f[i] * C(c1 + c2 - 1, c1) % P);
      Inc(as, 1ll * tp * f2[n - c1 - c2 - 1] % P);
    } else {
      int tp = 0;
      Dec(tp, 1ll * x * C(c1 + c2 - 1, c1) % P);
      if (c1 > 1)
        Dec(tp, 1ll * f[i - 1] * C(c1 + c2 - 2, c1) % P);
      Inc(tp, 1ll * g[i + 1] * C(c1 + c2 - 2, c1 - 1) % P);
      Inc(as, 1ll * tp * f2[n - c1 - c2] % P);
    }
  }
  printf("%d\n", as);
}
int main() {
  int T;
  scanf("%d", &T);
  while (T--)
    solve();
}