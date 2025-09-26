/*
 * Problem URL : https://codeforces.com/contest/2019/problem/F
 * Submit Date : 2025-09-11
 */

#include <bits/stdc++.h>
#define mem(_B, _E, _S) (memset((_B), (_E), (_S) * sizeof(*_B)))
char Getchar () {
  static char buf[1 << 22], *p1 = buf, *p2 = buf;
  return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 22, stdin), p1 == p2) ? EOF : *p1++;
}
void read (int &t) {
  t = 0; char ch = Getchar();
  while (!isdigit(ch)) ch = Getchar();
  while (isdigit(ch)) t = t * 10 + ch - '0', ch = Getchar();
}
const int N = 2e5 + 10;
using LL = long long;
int a[N], id[N];
int res, tag;
int fmx[2][N], siz[N], dsu[N], vis[N]; // 10101010 -> 1010|1010 or 10101|010
int mx;
int Find (int x) { return x == dsu[x] ? x : dsu[x] = Find(dsu[x]); }
int chkmx (int x) { return (siz[x] & 1) ? fmx[1][x] : (fmx[0][x] | fmx[1][x]); }
void Upd (int x, int t) {
  res += t * (siz[x] + 1) / 2;
  tag += t * chkmx(x);
}
void Merge (int x, int y) {
  x = Find(x), y = Find(y);
  if (x == y) return;
  Upd(x, -1), Upd(y, -1);
  int o = siz[x] & 1; //
  fmx[0][x] |= fmx[o][y];
  fmx[1][x] |= fmx[o ^ 1][y];
  siz[x] += siz[y]; //
  dsu[y] = x;
  Upd(x, 1);
}
void solve () {
  int n;
  read(n);
  for (int i = 1; i <= n; ++i) read(a[i]);
  for (int i = 1; i <= n; ++i) id[i] = i, dsu[i] = i;
  std::sort(id + 1, id + n + 1, [&] (int i, int j) { return a[i] > a[j]; });
    mx = a[id[1]], res = tag = 0;
    int ans = 0;
  mem(fmx[0], 0, n + 1), mem(fmx[1], 0, n + 1);
  mem(vis, 0, n + 1);
  std::fill(siz + 1, siz + n + 1, 1);
  for (int i = 1; i <= n; ++i) {
    int x = id[i];
    vis[x] = 1;
    fmx[1][x] = a[x] == mx;
    Upd(x, 1);
    if (x > 1 && vis[x - 1])
      Merge(x - 1, x); // notice the order
    if (x < n && vis[x + 1])
      Merge(x, x + 1);
    ans = std::max(ans, mx + a[x] + res - (tag == 0));
  }
  printf("%d\n", ans);
}
int main () {
  // freopen("data.in", "r", stdin);
  // freopen("data.out", "w", stdout);
  int T;
  read(T);
  while (T--) solve();
}
