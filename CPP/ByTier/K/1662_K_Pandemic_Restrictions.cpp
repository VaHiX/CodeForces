// Problem: CF 1662 K - Pandemic Restrictions
// https://codeforces.com/contest/1662/problem/K

/*
 * Problem: K. Pandemic Restrictions
 * 
 * Description:
 * Given three friends' houses at coordinates (x1, y1), (x2, y2), (x3, y3), 
 * find the minimum value of r such that there exists a point (residence) 
 * where the sum of distances for each pair of friends meeting at that point 
 * does not exceed r.
 * 
 * Approach:
 * This is a minimax optimization problem. We need to find a point that 
 * minimizes the maximum of the three meeting costs. The algorithm uses 
 * a gradient descent-like approach to iteratively improve the position 
 * by moving closer to the friend whose current meeting cost is highest.
 * 
 * Algorithms:
 * - Gradient descent optimization for minimizing the maximum
 * - Geometric calculations for distances and angles
 * 
 * Time Complexity: O(1) - The algorithm runs a fixed number of iterations
 * Space Complexity: O(1) - Only a constant amount of extra space used
 * 
 * Techniques:
 * - Geometric point and vector operations
 * - Distance and angle calculations
 * - Iterative optimization using gradient-like steps
 */

#include <math.h>
#include <stdio.h>
#include <time.h>
#include <algorithm>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

namespace Geometry {
struct point;
}  // namespace Geometry

using namespace std;
#define rep(i, a, n) for (int i = (a); i < (n); i++)
#define per(i, a, n) for (int i = (a) - 1; i >= (n); i--)
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define SZ(x) (int)x.size()
#define make_unique(x)                                                         \
  {                                                                            \
    sort(all(x));                                                              \
    x.resize(unique(all(x)) - x.begin());                                      \
  }
#define bug(x) cerr << #x << '=' << x << ' '
#define debug(x) cerr << #x << '=' << x << endl
mt19937 mrand(time(0));
typedef long long ll;
typedef pair<int, int> PII;
typedef vector<int> VI;
typedef double db;
const int mod = 1e9 + 7;
const ll inf = 1 << 30;
const int N = 1e6 + 5;
int n, m;
db ans;
namespace Geometry {
const db eps = (db)1e-8;
const db pi = (db)acos(-1.0);
int sgn(const db &x) { return x < -eps ? -1 : x > eps; }
#define vect point
struct point {
  db x, y;
  point() {}
  point(db _x, db _y) : x(_x), y(_y) {}
  point operator+(point s) { return point(x + s.x, y + s.y); }
  point operator-(point s) { return point(x - s.x, y - s.y); }
  point operator*(db k) { return point(x * k, y * k); }
  point operator/(db k) { return point(x / k, y / k); }
  db operator*(point p) { return x * p.x + y * p.y; }
  db operator^(point p) { return x * p.y - y * p.x; }
  bool operator<(point s) {
    return !sgn(x - s.x) ? sgn(y - s.y) < 0 : sgn(x - s.x) < 0;
  }
  bool operator>(point s) { return s < *this; }
  bool operator==(point s) { return !sgn(x - s.x) && !sgn(y - s.y); }
  bool operator<=(point s) { return !(*this > s); }
  bool operator>=(point s) { return !(*this < s); }
  bool operator!=(point s) { return !(*this == s); }
  db getl() { return x * x + y * y; }
  db len() { return sqrt(x * x + y * y); }
  db _tan() { return y / x; }
  db angle() const { return atan2(y, x); }
  db angle(point t) {
    db r = atan2((*this) ^ t, (*this) * t);
    return r;
  }
  point unit() { return *this / len(); }
  point unit_len(db d) { return unit() * d; }
  point normal() { return point(-y, x); }
  point symmetry(point s) { return s + s - *this; }
  point rotate(db a) {
    return point(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
  }
  db dot(point a, point b) { return (a - *this) * (b - *this); }
  db det(point a, point b) { return (a - *this) ^ (b - *this); }
};
db norm(db x) { return x * x; }
db dist(point a, point b) { return (a - b).len(); }
db angle(vect a, vect b) { return a.angle(b); }
db angle(point x, point s, point t) {
  vect xs = s - x, xt = t - x;
  return fabs(xs.angle(xt));
}
void print(point s) { bug(s.x), debug(s.y); }
bool in_line(point a, point b, point s) { return !sgn((s - a) ^ (s - b)); }
} // namespace Geometry
using namespace Geometry;
point a[N], b[N];
db gao(point s, point ss, point tt) {
  db res = 0;
  if (in_line(s, ss, tt)) {
    res = max(dist(s, ss), max(dist(s, tt), dist(ss, tt)));
  } else {
    db t = max({angle(s, ss, tt), angle(ss, s, tt), angle(tt, s, ss)});
    res = min({dist(s, ss) + dist(s, tt), dist(ss, tt) + dist(ss, s),
               dist(tt, ss) + dist(tt, s)});
    if (t < pi * 2 / 3) {
      db ag = angle(s, ss, tt);
      ag += pi / 3;
      db u = dist(s, ss), v = dist(s, tt);
      res = min(res, sqrt(norm(u) + norm(v) - 2 * u * v * cos(ag)));
    }
  }
  return res;
}
int main() {
  rep(i, 0, 3) scanf("%lf%lf", &b[i].x, &b[i].y);
  db t = 1, ans = 1e9;
  db f[3];
  point pos(2.3842, 0.4151);  // Starting initial position (from example)
  while (t > eps) {
    f[0] = gao(pos, b[0], b[1]);
    f[1] = gao(pos, b[1], b[2]);
    f[2] = gao(pos, b[0], b[2]);
    ans = min(ans, max({f[0], f[1], f[2]}));
    if (f[0] <= f[1] && f[0] <= f[2]) {
      pos = pos + (b[2] - pos) * t;  // Move towards friend 2 to reduce max cost
    } else if (f[1] <= f[0] && f[1] <= f[2]) {
      pos = pos + (b[0] - pos) * t;  // Move towards friend 0 to reduce max cost
    } else {
      pos = pos + (b[1] - pos) * t;  // Move towards friend 1 to reduce max cost
    }
    t *= 0.9;  // Decrease step size
  }
  printf("%.10lf\n", ans);
  return 0;
}


// https://github.com/VaHiX/CodeForces/