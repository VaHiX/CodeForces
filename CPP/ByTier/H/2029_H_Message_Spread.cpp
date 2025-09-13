/*
 * Problem URL : https://codeforces.com/contest/2029/problem/H
 * Submit Date : 2025-09-09
 */

#pragma GCC optimize(2, 3, "Ofast", "inline", "unroll-loops")
#pragma GCC optimize("-Ofast", "-finline", "-funroll-loops",                   \
                     "-fno-stack-protector")
#pragma GCC target("avx")
#include <bits/stdc++.h>
typedef int ll;
typedef long double ld;
typedef unsigned long long ull;
#define pii pair<ll, ll>
#define rep(i, a, b) for (ll i = (a); i <= (b); ++i)
#define per(i, a, b) for (ll i = (a); i >= (b); --i)
using namespace std;
bool Mbe;
ll read() {
  ll x = 0, f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-')
      f = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * f;
}
void write(ll x) {
  if (x < 0)
    putchar('-'), x = -x;
  if (x > 9)
    write(x / 10);
  putchar(x % 10 + '0');
}
const ll Mod = 998244353;
ll n, m, w[22][22], iw[22][22];
ll P[(1 << 21) + 9], iP[(1 << 21) + 9], f[(1 << 20) + 9], g[(1 << 20) + 9],
    h[(1 << 20) + 9], tmp[(1 << 20) + 9], pc[(1 << 21) + 9];
ll th[22][(1 << 20) + 9], tp[22][(1 << 20) + 9], coef1[(1 << 20) + 9];
ll pw(ll x, ll p) {
  ll res = 1;
  while (p) {
    if (p & 1)
      res = 1ll * res * x % Mod;
    x = 1ll * x * x % Mod, p >>= 1;
  }
  return res;
}
void Add(ll &x, ll y) {
  x += y;
  if (x >= Mod)
    x -= Mod;
}
void Dec(ll &x, ll y) {
  x -= y;
  if (x < 0)
    x += Mod;
}
void FWT(ll *f, ll n) {
  for (ll i = 1; i < (1 << n); i <<= 1) {
    for (ll j = 0; j < (1 << n); j += (i << 1)) {
      rep(k, 0, i - 1) Add(f[j + k + i], f[j + k]);
    }
  }
}
void IFWT(ll *f, ll n) {
  for (ll i = 1; i < (1 << n); i <<= 1) {
    for (ll j = 0; j < (1 << n); j += (i << 1)) {
      rep(k, 0, i - 1) Dec(f[j + k + i], f[j + k]);
    }
  }
}
bool Med;
int main() {
  cerr << fabs(&Med - &Mbe) / 1048576.0 << "MB\n";
  n = read(), m = read();
  rep(i, 0, n - 1) { rep(j, 0, n - 1) w[i][j] = iw[i][j] = 1; }
  while (m--) {
    ll x = read() - 1, y = read() - 1, p = read(), q = read();
    p = 1ll * p * pw(q, Mod - 2) % Mod;
    w[x][y] = w[y][x] = (1 - p + Mod) % Mod;
    iw[x][y] = iw[y][x] = pw(1 - p + Mod, Mod - 2);
  }
  rep(i, 1, (1 << n) - 1) pc[i] = pc[i ^ (i & (-i))] + 1;
  P[0] = 1, iP[0] = 1;
  rep(i, 1, (1 << n) - 1) {
    P[i] = P[i ^ (i & (-i))], iP[i] = iP[i ^ (i & (-i))];
    ll x = __lg(i & (-i));
    rep(j, 0, n - 1) {
      if (((i >> j) & 1))
        P[i] = 1ll * P[i] * w[x][j] % Mod, iP[i] = 1ll * iP[i] * iw[x][j] % Mod;
    }
  }
  rep(i, 1, (1 << n) - 2) {
    if (!(i & 1))
      continue;
    ll pb = 1ll * P[(1 << n) - 1] * iP[i] % Mod * iP[((1 << n) - 1) ^ i] % Mod;
    g[i >> 1] = pw(1 - pb + Mod, Mod - 2);
  }
  n--;
  rep(i, 0, (1 << n) - 1) coef1[i] = iP[(((1 << n) - 1) ^ i) << 1];
  f[0] = 1;
  rep(i, 0, n) {
    rep(j, 0, (1 << n) - 1) {
      if (pc[j] == i)
        tp[i][j] = P[(((1 << n) - 1) ^ j) << 1 | 1];
    }
    FWT(tp[i], n);
  }
  rep(i, 0, n - 1) {
    memset(tmp, 0, sizeof(tmp));
    rep(j, 0, (1 << n) - 1) {
      if (pc[j] == i) {
        tmp[j] = 1ll * iP[j << 1 | 1] * f[j] % Mod * g[j] % Mod;
        h[j] = (h[j] + 1ll * tmp[j] * P[(1 << (n + 1)) - 1]) % Mod;
      }
    }
    FWT(tmp, n);
    rep(j, 1, n - i) {
      rep(k, 0, (1 << n) - 1) {
        th[i + j][k] = (th[i + j][k] + 1ll * tmp[k] * tp[j][k]) % Mod;
      }
    }
    IFWT(th[i + 1], n);
    rep(j, 0, (1 << n) - 1) {
      if (pc[j] == i + 1)
        h[j] = th[i + 1][j];
    }
    memcpy(tmp, h, sizeof(h));
    rep(j, 0, (1 << n) - 1) tmp[j] = 1ll * tmp[j] * coef1[j] % Mod;
    rep(j, 0, n - 1) {
      per(k, (1 << n) - 1, 0) {
        if ((k >> j) & 1)
          Dec(tmp[k], tmp[k ^ (1 << j)]);
      }
    }
    rep(j, 0, (1 << n) - 1) {
      if (pc[j] == i + 1)
        f[j] = tmp[j];
    }
  }
  ll ans = 0;
  rep(i, 0, (1 << n) - 1) ans = (ans + 1ll * f[i] * g[i]) % Mod;
  write(ans), putchar('\n');
  cerr << "\n" << clock() * 1.0 / CLOCKS_PER_SEC * 1000 << "ms\n";
  return 0;
}