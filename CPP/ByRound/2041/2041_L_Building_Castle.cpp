/*
 * Problem URL : https://codeforces.com/contest/2041/problem/L
 * Submit Date : 2025-08-25
 */

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <math.h>
#include <numeric>
#include <queue>
#include <set>
#include <unordered_set>
#include <vector>

#define PI atan(1) * 4

using namespace std;

// initial observations:
// the center must necessarily be equal to the midpoint of the diameter
// of the polygon.
// given a center, can we calculate the min cost needed?
// center is a point such that it bisects any segment
// passing through it.
// this limits the possible set of polygons?
// given a center, let's compute the answer
// compute reflection of polygon

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template <class T> struct Point {
  typedef Point P;
  T x, y;
  // operators imply that point should be IN FRONT of the class it passes in
  explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
  bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
  bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
  P operator+(P p) const { return P(x + p.x, y + p.y); }
  P operator-(P p) const { return P(x - p.x, y - p.y); }
  P operator*(T d) const { return P(x * d, y * d); }
  P operator/(T d) const { return P(x / d, y / d); }
  T dot(P p) const { return x * p.x + y * p.y; }
  T cross(P p) const { return x * p.y - y * p.x; }
  T cross(P a, P b) const { return (a - *this).cross(b - *this); }
  T dist2() const { return x * x + y * y; }
  double dist() const { return sqrt((double)dist2()); }
  // angle to x-axis in interval [-pi, pi]
  double angle() const { return atan2(y, x); }
  P unit() const { return *this / dist(); } // makes dist()=1
  P perp() const { return P(-y, x); }       // rotates +90 degrees
  P normal() const { return perp().unit(); }
  // returns point rotated 'a' radians ccw around the origin
  P rotate(double a) const {
    return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
  }
  friend std::ostream &operator<<(std::ostream &os, P p) {
    return os << "(" << p.x << "," << p.y << ")";
  }
};

using P = Point<double>;

#define cmp(i, j) sgn(dir.perp().cross(poly[(i) % n] - poly[(j) % n]))
#define extr(i) cmp(i + 1, i) >= 0 && cmp(i, i - 1 + n) < 0
template <class P> int extrVertex(vector<P> &poly, P dir) {
  int n = poly.size(), lo = 0, hi = n;
  if (extr(0))
    return 0;
  while (lo + 1 < hi) {
    int m = (lo + hi) / 2;
    if (extr(m))
      return m;
    int ls = cmp(lo + 1, lo), ms = cmp(m + 1, m);
    (ls < ms || (ls == ms && ls == cmp(lo, m)) ? hi : lo) = m;
  }
  return lo;
}
const long double eps = 1e-9, inf = 1e9;
template <class T> struct Halfplane {
  // the halfplane determined by p and pq takes all points that are
  // _counterclockwise_ wrt p -> (p + pq) vector For boolean polygon
  // intersection where precision makes a big difference: see the last function!
  Point<T> p, pq;
  long double angle;

  Halfplane() {}
  Halfplane(const Point<T> &a, const Point<T> &b) : p(a), pq(b - a) {
    angle = atan2l(pq.y, pq.x);
  }

  bool out(const Point<T> &r) { return pq.cross(r - p) < -eps; }

  bool operator<(const Halfplane &e) const { return angle < e.angle; }

  friend Point<T> inter(const Halfplane &s, const Halfplane &t) {
    long double alpha = (t.p - s.p).cross(t.pq) / s.pq.cross(t.pq);
    return s.p + (s.pq * alpha);
  }
};

template <class T> vector<Point<T>> hp_intersect(vector<Halfplane<T>> &H) {
  // important note: H is changed within this function so make a copy if you
  // need it later!
  using P = Point<T>;
  using Halfplane = Halfplane<T>;
  P box[4] = {P(inf, inf), P(-inf, inf), P(-inf, -inf), P(inf, -inf)};

  for (int i = 0; i < 4; i++) {
    Halfplane aux(box[i], box[(i + 1) % 4]);
    H.push_back(aux);
  }
  sort(H.begin(), H.end());
  deque<Halfplane> dq;
  int len = 0;
  for (int i = 0; i < int(H.size()); i++) {
    while (len > 1 && H[i].out(inter(dq[len - 1], dq[len - 2]))) {
      dq.pop_back();
      --len;
    }

    while (len > 1 && H[i].out(inter(dq[0], dq[1]))) {
      dq.pop_front();
      --len;
    }

    if (len > 0 && fabsl(H[i].pq.cross(dq[len - 1].pq)) < eps) {
      if (H[i].pq.dot(dq[len - 1].pq) < 0.0) {
        return vector<P>();
      }

      if (H[i].out(dq[len - 1].p)) {
        dq.pop_back();
        --len;
      } else
        continue;
    }
    dq.push_back(H[i]);
    ++len;
  }

  while (len > 2 && dq[0].out(inter(dq[len - 1], dq[len - 2]))) {
    dq.pop_back();
    --len;
  }

  while (len > 2 && dq[len - 1].out(inter(dq[0], dq[1]))) {
    dq.pop_front();
    --len;
  }

  if (len < 3)
    return vector<P>();

  vector<P> ret(len);
  for (int i = 0; i + 1 < len; i++) {
    ret[i] = inter(dq[i], dq[i + 1]);
  }
  ret.back() = inter(dq[len - 1], dq[0]);
  return ret;
}

vector<P> get_intersection(vector<P> &poly1, vector<P> &poly2) {
  vector<Halfplane<double>> hps;
  for (int i = 0; i < poly1.size(); i++) {
    hps.push_back(Halfplane<double>(poly1[i], poly1[(i + 1) % poly1.size()]));
  }
  for (int i = 0; i < poly2.size(); i++) {
    hps.push_back(Halfplane<double>(poly2[i], poly2[(i + 1) % poly2.size()]));
  }
  vector<P> hull = hp_intersect(hps);

  return hull;
}

#define cmp(i, j) sgn(dir.perp().cross(poly[(i) % n] - poly[(j) % n]))
#define extr(i) cmp(i + 1, i) >= 0 && cmp(i, i - 1 + n) < 0
int extrVertex(vector<P> &poly, P dir) {
  int n = poly.size(), lo = 0, hi = n;
  if (extr(0))
    return 0;
  while (lo + 1 < hi) {
    int m = (lo + hi) / 2;
    if (extr(m))
      return m;
    int ls = cmp(lo + 1, lo), ms = cmp(m + 1, m);
    (ls < ms || (ls == ms && ls == cmp(lo, m)) ? hi : lo) = m;
  }
  return lo;
}

#define cmpL(i) sgn(a.cross(poly[i], b))
template <class P> array<int, 2> lineHull(P a, P b, vector<P> &poly) {
  int endA = extrVertex(poly, (a - b).perp());
  int endB = extrVertex(poly, (b - a).perp());
  if (cmpL(endA) < 0 || cmpL(endB) > 0)
    return {-1, -1};
  array<int, 2> res;
  for (int i = 0; i < 2; i++) {
    int lo = endB, hi = endA, n = poly.size();
    while ((lo + 1) % n != hi) {
      int m = ((lo + hi + (lo < hi ? 0 : n)) / 2) % n;
      (cmpL(m) == cmpL(endB) ? lo : hi) = m;
    }
    res[i] = (lo + !cmpL(hi)) % n;
    swap(endA, endB);
  }
  if (res[0] == res[1])
    return {res[0], -1};
  if (!cmpL(res[0]) && !cmpL(res[1]))
    switch ((res[0] - res[1] + poly.size() + 1) % poly.size()) {
    case 0:
      return {res[0], res[0]};
    case 2:
      return {res[1], res[1]};
    }
  return res;
}

double polygonArea2(vector<P> &v) {
  double a = v.back().cross(v[0]);
  for (int i = 0; i < v.size() - 1; i++) {
    a += v[i].cross(v[i + 1]);
  }
  return a;
}

double test_intersection(P d, vector<P> poly1, vector<P> poly2) {
  // runs in NlogN
  for (int i = 0; i < poly2.size(); i++) {
    poly2[i] = poly2[i] + d;
  }
  vector<P> hull = get_intersection(poly1, poly2);
  if (hull.empty() || hull.size() <= 2) {
    return -abs(d.x) * 4e4 - abs(d.y);
  }

  return polygonArea2(hull) / 2;
}

double ternary_y(double x, vector<P> poly1, vector<P> poly2) {
  double ymin = -4e4, ymax = 4e4;
  for (int step = 0; step < 60; step++) {
    double yl = (ymin * 51 + ymax * 49) / 100;
    double yr = (ymin * 49 + ymax * 51) / 100;

    double a = test_intersection(P(x, yl), poly1, poly2);
    double b = test_intersection(P(x, yr), poly1, poly2);
    if (a == b) {
      ymin = yl, ymax = yr;
    } else if (a > b) {
      ymax = yr;
    } else {
      ymin = yl;
    }
  }
  return test_intersection(P(x, ymax), poly1, poly2);
}

double ternary_x(vector<P> poly1, vector<P> poly2) {

  double xmin = -4e4, xmax = 4e4;
  for (int step = 0; step < 60; step++) {
    double xl = (xmin * 51 + xmax * 49) / 100;
    double xr = (xmin * 49 + xmax * 51) / 100;
    double a = ternary_y(xl, poly1, poly2), b = ternary_y(xr, poly1, poly2);
    if (a == b) {
      xmax = xr, xmin = xl;
    } else if (a > b) {
      xmax = xr;
    } else {
      xmin = xl;
    }
  }
  return ternary_y(xmax, poly1, poly2);
}

int main() {
  int n;
  cin >> n;
  vector<P> poly(n);
  P centroid;
  for (int i = 0; i < n; i++) {
    cin >> poly[i].x >> poly[i].y;
    centroid = centroid + poly[i];
  }
  centroid = centroid / n;
  for (int i = 0; i < n; i++)
    poly[i] = poly[i] - centroid;
  vector<P> rev_poly;
  for (int i = 0; i < n; i++) {
    rev_poly.push_back(poly[i] * -1);
  }
  vector<P> res = get_intersection(poly, rev_poly);
  cout << setprecision(24);
  double inter = ternary_x(poly, rev_poly);
  cout << polygonArea2(poly) / 2 - inter << "\n";
  // from here, can do a ternary search
  // want to  find some d such that when we shift rev_poly by d, that the area
  // of intersection is the greatest. i claim this goes up then down if we scan
  // over x / y so for a given d, how to calculat ehte inttersection area? remap
  // it to +d, and then issues with 0s? just center the polygon, that way i know
  // that 0 will converge to a nonzero region.... so easy to think of ugh`
}
