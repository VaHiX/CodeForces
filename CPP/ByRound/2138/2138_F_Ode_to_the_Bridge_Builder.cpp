/*
 * Problem URL : https://codeforces.com/contest/2138/problem/F
 * Submit Date : 2025-09-09
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const double EPS_SGN = 1e-13;

inline int sgn(double x) {
  if (x > EPS_SGN)
    return 1;
  if (x < -EPS_SGN)
    return -1;
  return 0;
}

struct Point {
  double x, y;
  Point(double _x = 0.0, double _y = 0.0) : x(_x), y(_y) {}
};
Point operator+(const Point &a, const Point &b) {
  return Point(a.x + b.x, a.y + b.y);
}
Point operator-(const Point &a, const Point &b) {
  return Point(a.x - b.x, a.y - b.y);
}
Point operator*(double k, const Point &p) { return Point(k * p.x, k * p.y); }

inline double dot(const Point &a, const Point &b) {
  return a.x * b.x + a.y * b.y;
}
inline double det(const Point &a, const Point &b) {
  return a.x * b.y - a.y * b.x;
}
inline double len(const Point &a) {
  return sqrt(max(0.0, a.x * a.x + a.y * a.y));
}

// project point x onto line (ya -> yb)
Point project_point(const Point &x, const Point &ya, const Point &yb) {
  Point v = yb - ya;
  double d = dot(v, v);
  if (d == 0)
    return ya;
  return ya + (dot(v, x - ya) / d) * v;
}

// distance from x to line (ya->yb)
double distp(const Point &x, const Point &ya, const Point &yb) {
  return fabs(det(ya - x, yb - x)) / len(yb - ya);
}

// intersection point on the line through la-lb whose distance to o is 1 and on
// the same side as lb
Point line_circle_intersec_point(const Point &o, const Point &la,
                                 const Point &lb) {
  double dis = distp(o, la, lb);
  Point pj = project_point(o, la, lb);
  double inside = 1.0 - dis * dis;
  if (inside < 0)
    inside = 0;
  double l = sqrt(inside);
  Point dir = lb - la;
  double L = len(dir);
  if (L == 0)
    return pj;
  Point ret = pj + (l / L) * dir;
  return ret;
}

const int MAXN = 1000005;
tuple<int, int, int> ans[MAXN];
Point p[MAXN];
Point target;
int stepAllowed;

// check the constructed sequence is valid (debugging / safety)
bool check(int nOps) {
  set<pair<int, int>> st;
  st.insert({1, 2});
  if (nOps > stepAllowed)
    return false;
  double eps_len = 1e-8, eps_dis = 1e-4;
  bool reached = false;
  for (int i = 1; i <= nOps; ++i) {
    auto [u, v, w] = ans[i];
    int a = u, b = v;
    if (a > b)
      swap(a, b);
    if (!st.count({a, b}))
      return false;
    if (len(p[a] - p[w]) < 0.5 - eps_len || len(p[a] - p[w]) > 1.0 + eps_len)
      return false;
    if (len(p[b] - p[w]) < 0.5 - eps_len || len(p[b] - p[w]) > 1.0 + eps_len)
      return false;
    st.insert({a, w});
    st.insert({b, w});
    if (len(p[w] - target) <= eps_dis)
      reached = true;
  }
  return reached;
}

// Case 1a: parallelogram stacking from A(0,0) towards target (using segments
// with endpoints on both base points)
int solve1a() {
  Point dir = target - p[1];
  int split = (int)ceil(len(dir) - 1e-9);
  int c = 2;
  for (int i = 1; i < split; ++i) {
    ++c;
    p[c] = p[1] + (1.0 * i / split) * dir;
    ans[c - 2] = {c - 2, c - 1, c};
    ++c;
    p[c] = p[2] + (1.0 * i / split) * dir;
    ans[c - 2] = {c - 2, c - 1, c};
  }
  ++c;
  p[c] = target;
  ans[c - 2] = {c - 2, c - 1, c};
  if (check(c - 2))
    return c - 2;
  return 0;
}

// Case 1b: parallelogram stacking from B(1,0) towards target
int solve1b() {
  Point dir = target - p[2];
  int split = (int)ceil(len(dir) - 1e-9);
  int c = 2;
  for (int i = 1; i <= split; ++i) {
    ++c;
    p[c] = p[1] + (1.0 * i / split) * dir;
    ans[c - 2] = {c - 2, c - 1, c};
    ++c;
    p[c] = p[2] + (1.0 * i / split) * dir;
    ans[c - 2] = {c - 2, c - 1, c};
  }
  if (check(c - 2))
    return c - 2;
  return 0;
}

// Case 2: make an intermediate triangle with angle 30deg and then parallelogram
// stacking
int solve2() {
  p[3] = Point(sqrt(3.0) / 2.0, 0.5);
  p[4] = line_circle_intersec_point(p[3], p[2], target);
  if (len(p[4] - p[2]) > 1.0)
    p[4] = p[2] + (1.0 / len(target - p[2])) * (target - p[2]);
  ans[1] = {1, 2, 3};
  ans[2] = {2, 3, 4};
  Point dir = target - p[4];
  int split = (int)ceil(len(dir) - 1e-9);
  int c = 4;
  for (int i = 1; i <= split; ++i) {
    ++c;
    p[c] = p[3] + (1.0 * i / split) * dir;
    ans[c - 2] = {c - 2, c - 1, c};
    ++c;
    p[c] = p[4] + (1.0 * i / split) * dir;
    ans[c - 2] = {c - 2, c - 1, c};
  }
  if (check(c - 2))
    return c - 2;
  return 0;
}

// Case 3a: use an initial equilateral up above A, then stack from B side
int solve3a() {
  p[3] = Point(0.5, sqrt(3.0) / 2.0);
  ans[1] = {1, 2, 3};
  Point dir = target - p[2];
  int split = (int)ceil(len(dir) - 1e-9);
  int c = 3;
  for (int i = 1; i < split; ++i) {
    ++c;
    p[c] = p[2] + (1.0 * i / split) * dir;
    ans[c - 2] = {c - 2, c - 1, c};
    ++c;
    p[c] = p[3] + (1.0 * i / split) * dir;
    ans[c - 2] = {c - 2, c - 1, c};
  }
  ++c;
  p[c] = target;
  ans[c - 2] = {c - 2, c - 1, c};
  if (check(c - 2))
    return c - 2;
  return 0;
}

// Case 3b: similar but stacking the other way
int solve3b() {
  p[3] = Point(0.5, sqrt(3.0) / 2.0);
  ans[1] = {1, 2, 3};
  Point dir = target - p[3];
  int split = (int)ceil(len(dir) - 1e-9);
  int c = 3;
  for (int i = 1; i <= split; ++i) {
    ++c;
    p[c] = p[2] + (1.0 * i / split) * dir;
    ans[c - 2] = {c - 2, c - 1, c};
    ++c;
    p[c] = p[3] + (1.0 * i / split) * dir;
    ans[c - 2] = {c - 2, c - 1, c};
  }
  if (check(c - 2))
    return c - 2;
  return 0;
}

int solve_all_cases() {
  if (int res = solve1a())
    return res;
  if (int res = solve1b())
    return res;
  if (int res = solve2())
    return res;
  if (int res = solve3a())
    return res;
  if (int res = solve3b())
    return res;
  return 0;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  p[1] = Point(0.0, 0.0);
  p[2] = Point(1.0, 0.0);

  int T;
  if (!(cin >> T))
    return 0;
  cout.setf(std::ios::fixed);
  cout << setprecision(12);
  while (T--) {
    int px, py, given_m;
    cin >> px >> py >> given_m;
    // recompute allowed steps (editorial uses this recomputed value)
    stepAllowed = (int)ceil(2.0 * sqrt(1.0 * px * px + 1.0 * py * py));
    target = Point((double)px, (double)py);

    int nOps = solve_all_cases();
    if (nOps == 0) {
      // Fallback: shouldn't happen for valid inputs, but try a trivial
      // approach: Place the target directly if possible from segment (1,2)
      // We'll create intersection of circles radius 1 around p1 and p2
      // (equilateral) and then try to move along (editorial's solver should
      // always find a solution; keep this just in case) As a minimal fallback
      // just output 1 equilateral triangle and then a step-by-step chain (rare)
      // but to be safe, assert false:
      assert(false && "No construction found (unexpected).");
    }

    cout << nOps << "\n";
    for (int i = 1; i <= nOps; ++i) {
      auto [u, v, w] = ans[i];
      // print u, v, x_w, y_w
      cout << u << ' ' << v << ' ' << p[w].x << ' ' << p[w].y << '\n';
    }
  }
  return 0;
}