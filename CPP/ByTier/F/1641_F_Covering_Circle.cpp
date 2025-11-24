// Problem: CF 1641 F - Covering Circle
// https://codeforces.com/contest/1641/problem/F

/*
 * Problem: F. Covering Circle
 *
 * Algorithm:
 * - Use binary search on the radius of the circle
 * - For each radius, check if there exists a subsegment of length l and a
 * circle of that radius that covers at least k points from that subsegment
 * - To efficiently check for each point, use a window-based sweep with
 * coordinate compression
 * - Use a segment tree to maintain the count of intervals covering a point
 *
 * Time Complexity: O(n * log(max_dist) * log(n)) where max_dist is roughly 2 *
 * 1e8 and n <= 50000 Space Complexity: O(n) for storage of points and auxiliary
 * data structures
 */

#include <algorithm>
#include <cmath>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <vector>

#define For(i, a, b) for (int i = (a); i <= (b); ++i)
#define Rep(i, a, b) for (int i = (a); i >= (b); --i)
using namespace std;
inline int read() {
  char c = getchar();
  int x = 0;
  bool f = 0;
  for (; !isdigit(c); c = getchar())
    f ^= !(c ^ 45);
  for (; isdigit(c); c = getchar())
    x = (x << 1) + (x << 3) + (c ^ 48);
  if (f)
    x = -x;
  return x;
}
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
typedef pair<int, int> pii;
typedef vector<int> vi;
#define maxn 200005
#define inf 0x3f3f3f3f
const double pi = acos(-1.0);
int mod = 3000007;
int H(int x, int y) { return ((1ull * x) << 32 | (1ull * y)) % mod; }
int s[maxn << 2], t[maxn << 2];
void up(int p) {
  t[p] = max(t[p << 1], s[p << 1] + t[p << 1 | 1]);
  s[p] = s[p << 1] + s[p << 1 | 1];
}
void addx(int x, int y) {
  x += 1 << 16;
  s[x] += y, t[x] = max(s[x], 0);
  while (x >>= 1)
    up(x);
}
void clr(int x) {
  x += 1 << 16;
  while (x)
    s[x] = t[x] = 0, x >>= 1;
}
int B, n, L, k, x[maxn], y[maxn], hx[maxn];
double dist(int u, int v) {
  return sqrt(1.0 * (x[u] - x[v]) * (x[u] - x[v]) +
              1.0 * (y[u] - y[v]) * (y[u] - y[v]));
}
double R;
vi v[3000010];
void build(int l, int r) {
  if (B)
    For(i, l, r) v[hx[i]].clear();
  B = R * 2 + 1;
  For(i, l, r) hx[i] = H(x[i] / B, y[i] / B), v[hx[i]].pb(i);
}
void add(int x, int y) {
  addx(x, y);
  if (x + L <= n)
    addx(x + L, -y);
}
void clear(int x) {
  clr(x);
  if (x + L <= n)
    clr(x + L);
}
bool chk(int u, double r) {
  vector<pair<double, int>> o;
  int xx = x[u] / B, yy = y[u] / B;
  For(dx, -1, 1) For(dy, -1, 1) {
    for (auto i : v[H(xx + dx, yy + dy)])
      if (i != u && abs(i - u) < L) {
        double dt = dist(u, i) / (2.0 * r);
        if (dt >= 1)
          continue;
        double ang = atan2(y[i] - y[u], x[i] - x[u]);
        dt = acos(dt);
        double al = ang - dt, ar = ang + dt;
        if (al < -pi || ar > pi)
          add(i, 1);
        if (al < -pi)
          al += 2 * pi;
        if (ar > pi)
          ar -= 2 * pi;
        o.pb(mkp(al, i));
        o.pb(mkp(ar, -i));
      }
  }
  sort(o.begin(), o.end());
  bool ok = (t[1] >= k - 1);
  for (auto t : o) {
    if (ok)
      break;
    add(abs(t.se), t.se > 0 ? 1 : -1);
    ok = (::t[1] >= k - 1);
  }
  for (auto t : o)
    clear(abs(t.se));
  return ok;
}
void del(int x) { v[hx[x]].erase(v[hx[x]].begin()); }
void ins(int u) { v[hx[u] = H(x[u] / B, y[u] / B)].pb(u); }
void work() {
  n = read(), L = read(), k = read();
  For(i, 1, n) x[i] = read(), y[i] = read(), x[i] += 1e8, y[i] += 1e8;
  R = 225675834 * sqrt((k - 1.) / L);
  build(1, L);
  For(i, 1, n) {
    if (i > L)
      del(i - L);
    if (chk(i, R)) {
      double l = 0, r = R;
      while (r - l >= l * 1e-10) {
        double mid = (l + r) / 2;
        if (chk(i, mid))
          r = mid;
        else
          l = mid;
      }
      R = l;
      build(max(i - L, 0) + 1, min(i + L - 1, n));
    }
    if (i + L <= n)
      ins(i + L);
  }
  For(i, n - L + 1, n) v[hx[i]].clear();
  printf("%.10lf\n", R);
}
signed main() {
  int T = read();
  while (T--)
    work();
  return 0;
}

// https://github.com/VaHiX/CodeForces/