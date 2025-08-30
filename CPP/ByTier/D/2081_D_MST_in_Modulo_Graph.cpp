/*
 * Problem URL : https://codeforces.com/problemset/problem/2081/D
 * Submit Date : 2025-08-23
 */

#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 5;
int T, n, a[N], f[N], l, m, r[N], c[N], fa[N], ans;
struct edge {
  int u, v, w;
} _e[N * 15], e[N * 15];
int find(int u) { return u == fa[u] ? u : fa[u] = find(fa[u]); }
int main() {
  cin >> T;
  while (T--) {
    scanf("%d", &n), l = m = ans = 0;
    for (int i = 1; i <= n; i++)
      scanf("%d", &a[i]), f[a[i]] = 1, l = max(l, a[i]);
    n = 0;
    for (int i = 1; i <= l; i++)
      if (f[i])
        a[++n] = i;
    for (int i = 1; i < n; i++)
      _e[++m] = (edge){a[i], a[i + 1], a[i + 1] % a[i]};
    for (int i = l; i; i--)
      r[i] = f[i] ? i : r[i + 1], f[i] = 0;
    for (int i = 1; i <= n; i++)
      for (int j = a[i] << 1; j <= l; j += a[i])
        if (r[j] - j < a[i])
          _e[++m] = (edge){a[i], r[j], r[j] - j};
    for (int i = 1; i <= m; i++)
      c[_e[i].w]++;
    for (int i = 1; i <= l; i++)
      c[i] += c[i - 1];
    for (int i = m; i; i--)
      e[c[_e[i].w]--] = _e[i];
    for (int i = 1; i <= l; i++)
      fa[i] = i, c[i] = 0;
    for (int i = 1, t = 0; i <= m && t < n - 1; i++) {
      int u = find(e[i].u), v = find(e[i].v);
      if (u ^ v)
        fa[v] = u, t++, ans += e[i].w;
    }
    printf("%d\n", ans);
  }
}