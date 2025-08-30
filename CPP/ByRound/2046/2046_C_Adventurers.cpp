/*
 * Problem URL : https://codeforces.com/problemset/submit
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
typedef pair<int, int> pii;
int T, n, m, y[N], c[N], c0[N << 2], c1[N << 2], c0l, c1l, c0r, c1r, res, pos,
    ans, X, Y;
pii p[N];
void build(int p, int l, int r) {
  c1[p] = 0;
  if (l == r)
    return void(c0[p] = c[l]);
  int mid = l + r >> 1;
  build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
  c0[p] = c0[p << 1] + c0[p << 1 | 1];
}
void update(int p, int l, int r, int y) {
  c0[p]--, c1[p]++;
  if (l == r)
    return;
  int mid = l + r >> 1;
  y <= mid ? update(p << 1, l, mid, y) : update(p << 1 | 1, mid + 1, r, y);
}
void query(int p, int l, int r) {
  if (l == r) {
    int t = min(min(c0l + c0[p], c1l + c1[p]), min(c0r, c1r));
    if (t > res)
      res = t, pos = p;
    return;
  }
  int mid = l + r >> 1;
  int t0 = min(c0l + c0[p << 1], c1l + c1[p << 1]),
      t1 = min(c0r + c0[p << 1 | 1], c1r + c1[p << 1 | 1]);
  if (min(t0, t1) > res)
    res = min(t0, t1), pos = mid;
  if (t0 > t1)
    c0r += c0[p << 1 | 1], c1r += c1[p << 1 | 1], query(p << 1, l, mid);
  else
    c0l += c0[p << 1], c1l += c1[p << 1], query(p << 1 | 1, mid + 1, r);
}
int main() {
  cin >> T;
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
      scanf("%d%d", &p[i].first, &p[i].second), y[i] = p[i].second, c[i] = 0;
    sort(y + 1, y + n + 1), m = unique(y + 1, y + n + 1) - y - 1;
    for (int i = 1; i <= n; i++)
      p[i].second = lower_bound(y + 1, y + m + 1, p[i].second) - y,
      c[p[i].second]++;
    build(1, 1, m);
    sort(p + 1, p + n + 1);
    ans = X = Y = 0;
    for (int i = 1; i <= n;) {
      int j = i;
      while (j <= n && p[j].first == p[i].first)
        update(1, 1, m, p[j++].second);
      c0l = c0r = c1l = c1r = res = 0, query(1, 1, m);
      if (res > ans)
        ans = res, X = p[i].first, Y = y[pos];
      i = j;
    }
    printf("%d\n%d %d\n", ans, X + 1, Y + 1);
  }
}