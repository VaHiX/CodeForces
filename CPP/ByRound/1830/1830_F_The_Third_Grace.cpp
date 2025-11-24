// Problem: CF 1830 F - The Third Grace
// https://codeforces.com/contest/1830/problem/F

/*
 * Problem: F. The Third Grace
 * 
 * Purpose: Maximize the sum of costs of all intervals by selecting a subset of points to activate.
 *          For each interval, its cost is the coefficient of the activated point with the largest coordinate within it.
 *          If there are no activated points in an interval, its cost is 0.
 * 
 * Algorithms/Techniques:
 *   - Segment tree with dynamic convex hull optimization (KTT - Kinetic Trajectory Tree)
 *   - Sorting intervals by right endpoint for processing
 *   - Dynamic updates to maintain optimal point selection for intervals
 * 
 * Time Complexity: O((n + m) * log m)
 * Space Complexity: O(m)
 * 
 * The solution uses a segment tree with dynamic convex hull optimization to efficiently maintain
 * the maximum coefficient value in each interval as points are activated.
 * 
 * The key idea is to process points in order and update interval costs dynamically.
 */

#include <stdio.h>
#include <algorithm>
#include <utility>

typedef long long ll;
using namespace std;
const ll inf = 0x3f3f3f3f3f3f3f3f;
const int N = 1e6 + 7;
struct Interval {
  int l, r;
  inline bool operator<(const Interval &rhs) const { return r < rhs.r; }
} a[N];
ll f[N];
int p[N];
int n, m;
template <class T = int> inline T read() {
  char c = getchar();
  bool sign = (c == '-');
  while (c < '0' || c > '9')
    c = getchar(), sign |= (c == '-');
  T x = 0;
  while ('0' <= c && c <= '9')
    x = (x << 1) + (x << 3) + (c & 15), c = getchar();
  return sign ? (~x + 1) : x;
}
namespace KTT {
struct Line {
  ll k, b;
  inline friend pair<Line, ll> cmp(Line a, Line b) {
    if (a.k == b.k ? a.b < b.b : a.k < b.k)
      swap(a, b);
    return a.b >= b.b ? make_pair(a, inf)
                      : make_pair(b, (b.b - a.b) / (a.k - b.k));
  }
};
struct Node {
  Line mx;
  ll t;
  inline friend Node operator+(const Node &a, const Node &b) {
    auto res = cmp(a.mx, b.mx);
    return (Node){res.first, min(min(a.t, b.t), res.second)};
  }
} nd[N << 2];
ll tag[N << 2];
inline int ls(int x) { return x << 1; }
inline int rs(int x) { return x << 1 | 1; }
inline void spread(int x, ll k) {
  nd[x].mx.b += nd[x].mx.k * k, nd[x].t -= k, tag[x] += k;
}
inline void pushdown(int x) {
  if (tag[x])
    spread(ls(x), tag[x]), spread(rs(x), tag[x]), tag[x] = 0;
}
void build(int x, int l, int r) {
  tag[x] = 0;
  if (l == r) {
    nd[x] = (Node){(Line){p[l], 0}, inf};
    return;
  }
  int mid = (l + r) >> 1;
  build(ls(x), l, mid), build(rs(x), mid + 1, r);
  nd[x] = nd[ls(x)] + nd[rs(x)];
}
void modify(int x, int l, int r, int p, ll k) {
  if (l == r) {
    nd[x].mx.b = k;
    return;
  }
  pushdown(x);
  int mid = (l + r) >> 1;
  if (p <= mid)
    modify(ls(x), l, mid, p, k);
  else
    modify(rs(x), mid + 1, r, p, k);
  nd[x] = nd[ls(x)] + nd[rs(x)];
}
void maintain(int x, int l, int r, ll k) {
  if (k <= nd[x].t) {
    spread(x, k);
    return;
  }
  pushdown(x);
  int mid = (l + r) >> 1;
  maintain(ls(x), l, mid, k), maintain(rs(x), mid + 1, r, k);
  nd[x] = nd[ls(x)] + nd[rs(x)];
}
void update(int x, int nl, int nr, int l, int r, ll k) {
  if (l <= nl && nr <= r) {
    maintain(x, nl, nr, k);
    return;
  }
  pushdown(x);
  int mid = (nl + nr) >> 1;
  if (l <= mid)
    update(ls(x), nl, mid, l, r, k);
  if (r > mid)
    update(rs(x), mid + 1, nr, l, r, k);
  nd[x] = nd[ls(x)] + nd[rs(x)];
}
} // namespace KTT
signed main() {
  int T = read();
  while (T--) {
    n = read(), m = read();
    for (int i = 1; i <= n; ++i)
      a[i].l = read(), a[i].r = read();
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= m; ++i)
      p[i] = read();
    KTT::build(1, 0, m);
    for (int i = 1, j = 1; i <= m; ++i) {
      KTT::modify(1, 0, m, i, f[i] = KTT::nd[1].mx.b);
      for (; j <= n && a[j].r == i; ++j)
        KTT::update(1, 0, m, a[j].l, i, 1);
    }
    printf("%lld\n", KTT::nd[1].mx.b);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/