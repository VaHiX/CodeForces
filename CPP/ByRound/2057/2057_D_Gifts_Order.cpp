/*
 * Problem URL : https://codeforces.com/problemset/problem/2057/D
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 2;
int T, n, q, a[N];
// max(a[r]-r)-min(a[l]-l)
// max(a[l]+l)-min(a[r]+r)
struct node {
  int xp, xm, np, nm, ans;
  void init(int i) { xp = np = a[i] + i, xm = nm = a[i] - i, ans = 0; }
} t[N * 4];
void pushup(int x) {
  node &s = t[x], &l = t[x * 2], &r = t[x * 2 + 1];
  s.xp = max(l.xp, r.xp);
  s.xm = max(l.xm, r.xm);
  s.np = min(l.np, r.np);
  s.nm = min(l.nm, r.nm);
  s.ans = max({l.ans, r.ans, r.xm - l.nm, l.xp - r.np});
}
void build(int x, int l, int r) {
  if (l == r)
    return t[x].init(l);
  int mid = (l + r) >> 1;
  build(x * 2, l, mid);
  build(x * 2 + 1, mid + 1, r);
  pushup(x);
}
void modify(int x, int l, int r, int L) {
  if (l == r)
    return t[x].init(l);
  int mid = (l + r) >> 1;
  L > mid ? modify(x * 2 + 1, mid + 1, r, L) : modify(x * 2, l, mid, L);
  pushup(x);
}
int main() {
  cin.tie(0)->sync_with_stdio(0);
  for (cin >> T; T--;) {
    cin >> n >> q;
    for (int i = 1; i <= n; ++i)
      cin >> a[i];
    build(1, 1, n);
    cout << t[1].ans << '\n';
    for (int x; q--;) {
      cin >> x;
      cin >> a[x];
      modify(1, 1, n, x);
      cout << t[1].ans << '\n';
    }
  }
  return 0;
}
