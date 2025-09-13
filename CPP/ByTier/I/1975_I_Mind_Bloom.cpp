/*
 * Problem URL : https://codeforces.com/contest/1975/problem/I
 * Submit Date : 2025-09-07
 */

// LUOGU_RID: 166060758
#include <bits/stdc++.h>
using namespace std;
const int P = 1e9 + 7, N = 125;
int T, n, a[N], inv[N], f[N][N][N], g[N][N][N], h[N], F[N][N], ct[N];
char s[N];
int ksm(int x, int y) {
  int res = 1;
  for (; y; y >>= 1, x = 1ll * x * x % P)
    if (y & 1)
      res = 1ll * res * x % P;
  return res;
}
inline void Add(int &x, int y) {
  if ((x += y) >= P)
    x -= P;
}
void DP(int i, int x) {
  if (!a[i])
    return f[i][x][x] = 1, void();
  int sum = a[i];
  for (int j = 1; j <= x; ++j)
    sum += a[j];
  if (sum >= n)
    return;
  if (x + a[i] >= n)
    return;
  int up = n;
  if (i < n && a[i] == a[i + 1]) {
    for (int j = i - 1; j <= i; ++j)
      for (int y = 0; y <= n; ++y)
        g[x][j][y] = 0;
    up = i + 1;
  } else {
    memset(g[x], 0, sizeof(g[x]));
    g[x][n][x + a[i]] = 1;
  }
  memset(h, 0, sizeof(h));
  int lim = x + a[i];
  for (int j = up; j >= i; --j)
    for (int y = j; y >= lim; --y)
      if (g[x][j][y]) {
        int p = 1ll * (y - x) * inv[j - x] % P;
        Add(g[x][j - 1][y], 1ll * (1 + P - p) * g[x][j][y] % P);
        p = 1ll * p * g[x][j][y] % P;
        for (int z = a[j] + y - 1; z <= j - 1; ++z) {
          if (j == i && y - 1 == x)
            Add(h[z], p);
          else
            Add(g[x][j - 1][z], 1ll * p * f[j][y - 1][z] % P);
        }
      }
  for (int y = x; y < i; ++y)
    f[i][x][y] = 1ll * g[x][i - 1][y] * ksm(1 + P - h[y], P - 2) % P;
}
void solve() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]);
  scanf("%s", s + 1);
  for (int i = 1; i <= n; ++i)
    ct[i] = ct[i - 1] + (s[i] == '1');
  if (ct[n] == n)
    return puts("1"), void();
  if (!ct[n])
    return puts("0"), void();
  if (a[1] > 1)
    return puts("1"), void();
  if (a[n] == 1)
    return puts("0"), void();
  memset(f, 0, sizeof(f));
  for (int i = n; i; --i)
    for (int x = i - 1; ~x; --x)
      DP(i, x);
  memset(F, 0, sizeof(F));
  F[0][0] = 1;
  for (int i = 1; i <= n; ++i)
    for (int x = ct[i]; x <= i; ++x) {
      for (int y = 0; y < i; ++y)
        Add(F[i][x], 1ll * f[i][x - 1][y] * F[i - 1][y] % P);
      if (s[i] == '1')
        continue;
      int p = 1ll * (x - ct[i]) * inv[i - ct[i]] % P;
      F[i][x] = 1ll * F[i][x] * p % P;
      Add(F[i][x], 1ll * (1 + P - p) * F[i - 1][x] % P);
    }
  printf("%d\n", (P + 1 - F[n][ct[n]]) % P);
}
int main() {
  for (int i = 1; i <= 120; ++i)
    inv[i] = ksm(i, P - 2);
  scanf("%d", &T);
  while (T--)
    solve();
  return 0;
}