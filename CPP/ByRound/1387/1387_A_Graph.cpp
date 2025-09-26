/*
 * Problem URL : https://codeforces.com/contest/1387/problem/A
 * Submit Date : 2025-09-02
 */

#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define fi first
#define se second
#define rep(i, j, k) for (int i = (j); i <= (k); i++)
#define per(i, j, k) for (int i = (j); i >= (k); i--)
const int N = 114514;
vector<pii> e[N];
int n, m, a[N], k[N], g[N], v[N], s[N], as[N], fl, po, x, y, z, kx;
void dfs(int x) {
  v[x] = 1;
  s[++po] = x;
  int y;
  for (pii w : e[x])
    if (v[y = w.fi]) {
      if (a[x] + a[y] == 0 && k[x] + k[y] != w.se)
        puts("NO"), exit(0);
      if (a[x] == a[y]) {
        int nk = (w.se - k[x] - k[y]) / (a[x] + a[y]);
        if (fl && nk != kx)
          puts("NO"), exit(0);
        else
          fl = 1, kx = nk;
      }
    } else
      a[y] = -a[x], k[y] = w.se - k[x], dfs(y);
}
int main() {
  scanf("%d%d", &n, &m);
  rep(i, 1, m) scanf("%d%d%d", &x, &y, &z), z *= 2, e[x].push_back({y, z}),
      e[y].push_back({x, z});
  rep(i, 1, n) if (!v[i]) {
    a[i] = 1;
    kx = k[i] = fl = po = 0;
    dfs(i);
    if (!kx) {
      rep(i, 1, po) g[i] = -k[s[i]] / a[s[i]];
      sort(g + 1, g + po + 1);
      kx = g[(po + 1) / 2];
    }
    rep(i, 1, po) as[s[i]] = kx * a[s[i]] + k[s[i]];
  }
  puts("YES");
  rep(i, 1, n) printf("%.2lf ", 0.5 * as[i]);
}
