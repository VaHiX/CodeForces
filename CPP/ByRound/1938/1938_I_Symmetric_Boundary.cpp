// Problem: CF 1938 I - Symmetric Boundary
// https://codeforces.com/contest/1938/problem/I

/*
 * Problem: Symmetric Boundary
 * Purpose: Determine the minimum area of a convex, point-symmetric region containing all vertices of a given convex polygon.
 * Algorithm: 
 *   - For each pair of edges from the input polygon (not parallel), generate potential symmetric boundaries.
 *   - Use line intersection to find candidate points for forming such boundaries.
 *   - Compute convex hulls of these candidates and calculate their areas.
 *   - Return the minimum valid area among all candidates.
 *
 * Time Complexity: O(n^5) due to nested loops over edges and vertices
 * Space Complexity: O(n^2) for storing intermediate polygon points and results
 */

#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;
const long long INF = 3LL << 59;
class point {
public:
  long long x, y;
  point() : x(0), y(0) {}
  point(long long x_, long long y_) : x(x_), y(y_) {}
  point operator-() const { return point(-x, -y); }
  point &operator+=(const point &p) {
    x += p.x;
    y += p.y;
    return *this;
  }
  point &operator-=(const point &p) {
    x -= p.x;
    y -= p.y;
    return *this;
  }
  point &operator*=(long long v) {
    x *= v;
    y *= v;
    return *this;
  }
  point operator+(const point &p) const { return point(*this) += p; }
  point operator-(const point &p) const { return point(*this) -= p; }
  point operator*(long long v) const { return point(*this) *= v; }
  long long dot(const point &p) const { return x * p.x + y * p.y; }
  long long cross(const point &p) const { return x * p.y - y * p.x; }
  bool operator<(const point &p) const { return x != p.x ? x < p.x : y < p.y; }
  bool operator==(const point &p) const { return x == p.x && y == p.y; }
};
// Computes cross point of two lines defined by (l0, l1) and (m0, m1)
pair<point, long long> cross_point(const point &l0, const point &l1,
                                   const point &m0, const point &m1) {
  long long t0 = (m0 - l0).cross(m1 - m0);
  long long t1 = (l1 - l0).cross(m1 - m0);
  if (t1 < 0) {
    t0 *= -1;
    t1 *= -1;
  }
  return make_pair(l0 * t1 + (l1 - l0) * t0, t1);
}
double solve(int n, const vector<point> &g) {
  vector<point> h0 = g; // Copy of input polygon vertices
  sort(h0.begin(), h0.end());
  vector<point> h1(n); // Temporary storage for transformed points
  vector<int> f(n);    // Flags to track which side of boundary each vertex is on
  vector<point> poly(2 * n + 2); // Stores computed polygon points (for hull)
  double ans = 1.0e+99; // Initialize answer to large value
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      int ni = (i + 1) % n, nj = (j + 1) % n;
      // Skip if the edges are collinear - no valid symmetric region can be formed
      if ((g[ni] - g[i]).cross(g[nj] - g[j]) == 0) {
        continue;
      }
      for (int k = 0; k < n; k++) { // Loop over all possible line segments from g[k]
        for (int l = 0; l < n; l++) { // Loop over all possible line segments from g[l]
          point l0 = g[k] + g[i]; // Start of first line segment
          point l1 = g[k] + g[ni]; // End of first line segment
          point m0 = g[l] + g[j]; // Start of second line segment
          point m1 = g[l] + g[nj]; // End of second line segment
          pair<point, long long> b = cross_point(l0, l1, m0, m1); 
          for (int x = 0; x < n; x++) {
            h1[x] = h0[x] * b.second; // Scale vertices appropriately
          }
          point pa = min(h1[0], b.first - h1[n - 1]); // Point A defining boundary line
          point pb = b.first - pa; // Vector B defining boundary line
          for (int x = 0; x < n; x++) {
            f[x] = ((pa - h1[x]).cross(pb - h1[x]) < 0 ? 1 : 2); // Flag based on cross product sign
          }
          int c0 = 0, c1 = n - 1;
          for (int x = 0; x < n; x++) {
            while (c0 != n && f[c0] != 1)
              c0++;
            while (c1 != -1 && f[c1] != 2)
              c1--;
            point p0 = (c0 != n ? h1[c0] : point(INF, 0));
            point p1 = (c1 != -1 ? b.first - h1[c1] : point(INF, 0));
            if (p0 < p1) {
              poly[x] = p0;
              c0++;
            } else {
              poly[x] = p1;
              c1--;
            }
          }
          for (int x = 0; x < n; x++) {
            poly[x + n] = b.first - poly[x]; // Reflect points about center point
          }
          int cnt = unique(poly.begin(), poly.begin() + 2 * n) - poly.begin(); // Remove duplicate points
          if (poly[0] == poly[cnt - 1]) {
            cnt--; // Adjust for wraparound
          }
          poly[cnt + 0] = poly[0]; // Close polygon
          poly[cnt + 1] = poly[1];
          double area = 0.0; // Initialize area calculation
          for (int x = 0; x < cnt; x++) {
            if ((poly[x + 1] - poly[x]).cross(poly[x + 2] - poly[x + 1]) < 0) {
              area = -1.0; // Invalid polygon (not concave) => not suitable for symmetric shape
              break;
            }
            area += poly[x].cross(poly[x + 1]);
          }
          if (area != -1.0) {
            area /= 2.0 * b.second * b.second; // Normalize the area
            ans = min(ans, area); // Update minimum area
          }
        }
      }
    }
  }
  return ans;
}
int main() {
  int n;
  cin >> n;
  vector<point> g(n);
  for (int i = 0; i < n; i++) {
    cin >> g[i].x >> g[i].y;
  }
  double ans = solve(n, g);
  if (ans == 1.0e+99) {
    cout << -1 << endl;
  } else {
    cout.precision(15);
    cout << fixed << ans << endl;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/