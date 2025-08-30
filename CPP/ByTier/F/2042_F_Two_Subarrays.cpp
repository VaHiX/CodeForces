/*
 * Problem URL : https://codeforces.com/contest/2042/problem/F
 * Submit Date : 2025-08-25
 */

#include <bits/stdc++.h>
#define int long long
#define pb push_back
#define SZ(x) (int)(x).size()
using namespace std;
const int N = 2e5 + 5, INF = 1e18;
int n, a[N], b[N], m, op, x, y;
struct node {
  int s, l, r, m, lm, rm, lr, mm;
  inline node operator+(node x) {
    return {s + x.s,
            max(l, s + x.l),
            max(x.r, x.s + r),
            max({m, x.m, r + x.l}),
            max({s + x.lm, l + x.m, lr + x.l, lm}),
            max({x.s + rm, x.r + m, x.lr + r, x.rm}),
            max({s + x.lr, l + x.r, lr + x.s}),
            max({x.mm, r + x.lm, m + x.m, rm + x.l, mm})};
  }
};
struct SGT {
#define ls (rt << 1)
#define rs (rt << 1 | 1)
  node t[N << 2];
  inline node mkn(int x) {
    return {a[x], a[x] + b[x], a[x] + b[x], a[x] + b[x] * 2,
            -INF, -INF,        -INF,        -INF};
  }
  inline void psu(int rt) { t[rt] = t[ls] + t[rs]; }
  void bld(int rt = 1, int l = 1, int r = n) {
    if (l == r) {
      t[rt] = mkn(l);
      return;
    }
    int mid = (l + r) >> 1;
    bld(ls, l, mid), bld(rs, mid + 1, r);
    psu(rt);
  }
  void upd(int x, int rt = 1, int l = 1, int r = n) {
    if (l == r) {
      t[rt] = mkn(x);
      return;
    }
    int mid = (l + r) >> 1;
    x <= mid ? upd(x, ls, l, mid) : upd(x, rs, mid + 1, r);
    psu(rt);
  }
  node qry(int L, int R, int rt = 1, int l = 1, int r = n) {
    if (l >= L && r <= R)
      return t[rt];
    int mid = (l + r) >> 1;
    if (R <= mid)
      return qry(L, R, ls, l, mid);
    if (L > mid)
      return qry(L, R, rs, mid + 1, r);
    return qry(L, R, ls, l, mid) + qry(L, R, rs, mid + 1, r);
  }
} T;
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  for (int i = 1; i <= n; i++)
    cin >> b[i];
  T.bld();
  cin >> m;
  while (m--) {
    cin >> op >> x >> y;
    if (op == 1)
      a[x] = y, T.upd(x);
    if (op == 2)
      b[x] = y, T.upd(x);
    if (op == 3)
      cout << T.qry(x, y).mm << '\n';
  }
  return 0;
}