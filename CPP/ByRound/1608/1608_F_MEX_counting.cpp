/*
 * Problem URL : https://codeforces.com/problemset/problem/1608/F
 * Submit Date : 2025-08-13
 */

// Hydro submission #668bde0f9741386c920e0152@1720442384761
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma target("avx512f,sse2,sse3,sse4,sse4.2")
using namespace std;
const int mod = 998244353;
inline void ensureMod(int &x) { x += (x >> 31) & mod; }

int n, m, b[2001], l[2001], r[2001];
int f[2][2001][2001], g[2001][2002];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    scanf("%d", b + i);
    l[i] = max(b[i] - m, 0);
    r[i] = min(b[i] + m, i);
  }
  for (int i = 2; i <= n; i++)
    l[i] = max(l[i], l[i - 1]);
  for (int i = n - 1; i >= 1; i--)
    r[i] = min(r[i], r[i + 1]);
  int now = 0;
  for (int i = l[n]; i <= r[n]; i++)
    f[now][i][1] = 1;
  for (int i = n - 1; i >= 1; i--) {
    now ^= 1;
    for (int j = l[i]; j <= r[i]; j++)
      memset(f[now][j], 0, sizeof(int) * (n + 1));
    for (int j = l[i + 1]; j <= r[i + 1]; j++)
      for (int k = 1; k <= n; k++) {
        if (!f[now ^ 1][j][k])
          continue;
        f[now][j][k] = (f[now][j][k] + (n - k + 1ll) * f[now ^ 1][j][k]) % mod;
        if (j)
          g[j - 1][k + 1] = f[now ^ 1][j][k];
      }
    for (int j = r[i + 1]; j > l[i]; j--)
      for (int k = 1; k <= n; k++) {
        g[j - 1][k] += g[j][k] - mod, ensureMod(g[j - 1][k]);
        g[j - 1][k + 1] -= g[j][k], ensureMod(g[j - 1][k + 1]);
      }
    for (int j = l[i]; j <= r[i]; j++)
      for (int k = 1; k <= n; k++)
        f[now][j][k] += g[j][k] - mod, ensureMod(f[now][j][k]);
    for (int j = l[i]; j <= r[i + 1]; j++)
      memset(g[j], 0, sizeof(int) * (n + 1));
  }
  long long answer = 0;
  for (int j = l[1]; j <= r[1]; j++)
    for (int k = 1; k <= n; k++)
      answer += 1ll * f[now][j][k] * (j ? 1 : n - k + 1) % mod;
  printf("%lld\n", answer % mod);
  return 0;
}