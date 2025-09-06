/*
 * Problem URL : https://codeforces.com/problemset/problem/2125/D
 * Submit Date : 2025-08-14
 */

#include <cstdio>
#include <utility>
#include <vector>
int n, m, mod = 998244353, p, q, ll, rr, mul = 1, f[200005];
int qpow(int a, int x) {
  int s = 1;
  for (; x; x >>= 1, a = 1ll * a * a % mod)
    if (x & 1)
      s = 1ll * s * a % mod;
  return s;
}
std::vector<std::pair<int, int>> g[200005];
int main() {
  scanf("%d%d", &m, &n);
  while (m--) {
    scanf("%d%d%d%d", &ll, &rr, &p, &q);
    p = 1ll * p * qpow(q, mod - 2) % mod;
    g[rr].push_back({ll, 1ll * p * qpow((mod + 1 - p) % mod, mod - 2) % mod});
    mul = 1ll * mul * (mod + 1 - p) % mod; // printf("%d\n",mul);
  } // printf("%d",qpow(9,mod-2));
  f[0] = 1;
  for (int i = 1; i <= n; i++)
    for (std::pair<int, int> j : g[i])
      f[i] = (f[i] + 1ll * j.second * f[j.first - 1]) % mod;
  printf("%lld", 1ll * mul * f[n] % mod);
}