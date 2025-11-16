// Problem: CF 1901 F - Landscaping
// https://codeforces.com/contest/1901/problem/F

/*
 * Problem: F. Landscaping
 * 
 * Algorithm: Convex Hull Trick with Dynamic Programming
 * 
 * Time Complexity: O(n log n)
 * Space Complexity: O(n)
 * 
 * Approach:
 * The problem requires finding optimal line segment y0 to y1 such that
 * the area between that segment and the polyline is minimized.
 * 
 * The solution uses a convex hull trick variant:
 * 1. Process the first half of points (1 to m) to compute prefix maximums
 * 2. Process the second half (m+1 to n) to compute suffix maximums
 * 3. For each point, we maintain a convex hull of lines
 * 4. For queries, we perform binary search on the hull to find optimal segment
 * 
 * The key insight is that the cost function can be expressed as a piecewise linear function,
 * and we need to maintain the convex hull to efficiently answer queries.
 */

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <string>

#pragma GCC optimize("Ofast,no-stack-protector,fast-math", 3)
using namespace std;
const int N = (1 << 21) + 10, M = 998244353;
using ll = long long;
using ul = unsigned long long;
using ld = double;
string s;
int T, n = 1e6 + 5, m, a[N], b[N];
ld nc;
struct dat {
  ld x, y;
  dat operator-(const dat &z) const { return {x - z.x, y - z.y}; }
  ll operator*(const dat &z) const { return x * z.y - y * z.x; }
  ld operator()(const ld &p, const ld &q) {
    return ld(y * p + x * q) / (x + p);
  }
} d[N];
int stk[N], tp;
ld sol(ld p, ld u) {
  int L = 1, R = tp, md;
  while (L < R) {
    md = L + R >> 1;
    if (d[stk[md + 1]](p, u) > d[stk[md]](p, u))
      L = md + 1;
    else
      R = md;
  }
  return d[stk[L]](p, u) * 2;
}
ld pr[N], to[N];
int main() {
  ios::sync_with_stdio(false);
  int i, j, k, l, r, x, y, z;
  cin >> n;
  for (i = 1; i <= n; ++i)
    cin >> a[i];
  for (i = 1; i <= n; ++i)
    cin >> b[i];
  m = n + 1 >> 1, nc = (1. + n) / 2;
  for (x = m + 1; x <= n; ++x) {
    d[x] = {x - nc, a[x]};
    while (tp > 1 &&
           (d[stk[tp]] - d[stk[tp - 1]]) * (d[x] - d[stk[tp - 1]]) >= 0)
      --tp;
    stk[++tp] = x;
  }
  pr[0] = to[m + 1] = -1e18;
  for (x = 1; x <= m; ++x)
    pr[x] = max(pr[x - 1], sol(nc - x, b[x]));
  for (x = m; x; --x)
    to[x] = max(to[x + 1], sol(nc - x, a[x]));
  for (x = 1; x <= m; ++x)
    printf("%.12lf ", max(pr[x], to[x + 1]));
  for (x = m, tp = 0; x; --x) {
    d[x] = {nc - x, b[x]};
    while (tp > 1 &&
           (d[stk[tp]] - d[stk[tp - 1]]) * (d[x] - d[stk[tp - 1]]) >= 0)
      --tp;
    stk[++tp] = x;
  }
  pr[m] = to[n + 1] = -1e18;
  for (x = m + 1; x <= n; ++x)
    pr[x] = max(pr[x - 1], sol(x - nc, b[x]));
  for (x = n; x > m; --x)
    to[x] = max(to[x + 1], sol(x - nc, a[x]));
  for (x = m + 1; x <= n; ++x)
    printf("%.12lf ", max(pr[x], to[x + 1]));
  return 0;
}


// https://github.com/VaHiX/CodeForces/