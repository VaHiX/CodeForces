/*
 * Problem URL : https://codeforces.com/contest/2030/problem/F
 * Submit Date : 2025-09-09
 */

#include <cstdio>
const int rSiz = 1 << 21;
char rBuf[rSiz], *p1 = rBuf, *p2 = rBuf;
#define gc()                                                                   \
  (p1 == p2 && (p2 = (p1 = rBuf) + fread(rBuf, 1, rSiz, stdin), p1 == p2)      \
       ? EOF                                                                   \
       : *p1++)
template <class T> void rd(T &x) {
  char ch = gc();
  for (; ch < '0' || ch > '9'; ch = gc())
    ;
  for (x = 0; ch >= '0' && ch <= '9'; ch = gc())
    x = (x << 1) + (x << 3) + (ch ^ 48);
}
#include <algorithm>
const int _ = 2e5 + 5;
int n, q, a[_], b[_], t[_ << 2], ans[_];
void Bld(int x, int l, int r) {
  t[x] = 0;
  if (l == r)
    return;
  int m = (l + r) >> 1;
  Bld(x << 1, l, m), Bld(x << 1 | 1, m + 1, r);
}
void Chg(int x, int l, int r, int w, int v) {
  if (l == r)
    return t[x] = v, void();
  int m = (l + r) >> 1;
  if (w <= m)
    Chg(x << 1, l, m, w, v);
  else
    Chg(x << 1 | 1, m + 1, r, w, v);
  t[x] = std::max(t[x << 1], t[x << 1 | 1]);
  ;
}
int Qry(int x, int l, int r, int L, int R) {
  if (R < l || r < L)
    return 0;
  if (L <= l && r <= R)
    return t[x];
  int m = (l + r) >> 1;
  return std::max(Qry(x << 1, l, m, L, R), Qry(x << 1 | 1, m + 1, r, L, R));
}
void solve() {
  rd(n), rd(q);
  Bld(1, 1, n);
  for (int i = 1; i <= n; i++)
    rd(a[i]), b[i] = 0;
  for (int i = 1, l = 1, r; i <= n; i++) {
    r = b[a[i]];
    for (; Qry(1, 1, n, l, r) > r; l++)
      ;
    if (r)
      Chg(1, 1, n, r, i);
    ans[i] = l;
    b[a[i]] = i;
  }
  for (int i = 1, l, r; i <= q; i++) {
    rd(l), rd(r);
    if (l < ans[r])
      printf("NO\n");
    else
      printf("YES\n");
  }
}
int main() {
  int T;
  rd(T);
  for (; T; T--)
    solve();
}
