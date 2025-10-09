// Problem: CF 2023 F - Hills and Pits
// https://codeforces.com/contest/2023/problem/F

/*
F. Hills and Pits
Algorithms: Segment Tree + Offline Processing + Two Pointers + Prefix Sums
Time Complexity: O(n * log n + q * log q)
Space Complexity: O(n)

This problem involves finding the minimum time for a dump truck to level sand in segments of a road, where each section has a height that needs to be adjusted to zero.
We use a segment tree with range maximum queries to efficiently compute the maximum subarray sum (Kadane's algorithm variant).
The approach handles each query by processing ranges and leveraging prefix sums to determine optimal movement strategies.
*/

#include <stdio.h>
#include <algorithm>
#include <utility>

using namespace std;
const int N = 3e5 + 5;
int T, n, q, a[N], ans[N];
long long s[N];
struct node {
  int l, r, id;
  bool operator<(const node &u) const { return s[l - 1] > s[u.l - 1]; }
} b[N];
struct node2 {
  long long x;
  int id;
  bool operator<(const node2 &u) const { return x > u.x; }
} c[N];
struct sgt {
  int s, lx, rx, mx;
  sgt operator+(const sgt &u) const {
    sgt v;
    v.s = s + u.s;
    v.lx = max(lx, s + u.lx);
    v.rx = max(u.rx, u.s + rx);
    v.mx = max(mx, max(u.mx, rx + u.lx));
    return v;
  }
} tr[N << 2];
inline void build(int u, int l, int r) {
  if (l == r)
    return tr[u] = {-1, -1, -1, -1}, void();
  int mid = (l + r) >> 1;
  build(u << 1, l, mid);
  build(u << 1 | 1, mid + 1, r);
  tr[u] = tr[u << 1] + tr[u << 1 | 1];
  return;
}
inline void upd(int u, int l, int r, int x) {
  if (l == r)
    return tr[u] = {1, 1, 1, 1}, void();
  int mid = (l + r) >> 1;
  if (x <= mid)
    upd(u << 1, l, mid, x);
  else
    upd(u << 1 | 1, mid + 1, r, x);
  tr[u] = tr[u << 1] + tr[u << 1 | 1];
  return;
}
inline sgt qry(int u, int l, int r, int L, int R) {
  if (L <= l && r <= R)
    return tr[u];
  int mid = (l + r) >> 1;
  if (R <= mid)
    return qry(u << 1, l, mid, L, R);
  if (L > mid)
    return qry(u << 1 | 1, mid + 1, r, L, R);
  return qry(u << 1, l, mid, L, R) + qry(u << 1 | 1, mid + 1, r, L, R);
}
inline int query(int l, int r) { return l > r ? 0 : qry(1, 1, n, l, r).mx; }
inline void solve() {
  for (int i = 1; i <= n; ++i)
    s[i] = s[i - 1] + a[i], c[i] = {s[i], i};
  c[n + 1] = {0, 0};
  sort(b + 1, b + 1 + q);
  sort(c + 1, c + 2 + n);
  build(1, 1, n);
  for (int i = 1, r, j = 1; i <= n + 1; i = r + 1) {
    for (r = i; r <= n && c[r + 1].x == c[i].x; ++r)
      ;
    for (int j = i; j <= r; ++j)
      if (c[j].id)
        upd(1, 1, n, c[j].id);
    for (; j <= q && s[b[j].l - 1] == c[i].x; ++j)
      ans[b[j].id] = max(ans[b[j].id], query(b[j].l, b[j].r - 1));
  }
  return;
}
inline void work() {
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; ++i)
    scanf("%d", a + i);
  for (int i = 1; i <= q; ++i)
    scanf("%d%d", &b[i].l, &b[i].r), ans[i] = 0, b[i].id = i;
  solve();
  for (int i = 1; i * 2 <= n; ++i)
    swap(a[i], a[n + 1 - i]);
  for (int i = 1; i <= q; ++i)
    b[i].l = n + 1 - b[i].l, b[i].r = n + 1 - b[i].r, swap(b[i].l, b[i].r);
  solve();
  for (int i = 1; i <= q; ++i) {
    if (s[b[i].r] < s[b[i].l - 1])
      ans[b[i].id] = -1;
    else
      ans[b[i].id] = 2 * (b[i].r - b[i].l) - ans[b[i].id];
  }
  for (int i = 1; i <= q; ++i)
    printf("%d\n", ans[i]);
  return;
}
int main() {
  scanf("%d", &T);
  while (T--)
    work();
  return 0;
}


// https://github.com/VaHiX/codeForces/