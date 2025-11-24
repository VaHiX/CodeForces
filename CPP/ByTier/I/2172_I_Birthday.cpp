// Problem: CF 2172 I - Birthday
// https://codeforces.com/contest/2172/problem/I

/*
Code Purpose:
This program solves the problem of cutting a circular cake (centered at origin with radius r) into two pieces using a straight line such that all strawberries lie on one side, and the smaller piece is maximized in area.

Algorithm:
1. Given n strawberries (points), compute the convex hull of these points.
2. For each edge of the convex hull, calculate the area of the smaller piece if we cut the cake along a line perpendicular to this edge and passing through the farthest point from the center.
3. The maximum such area among all edges gives the maximum possible area of the smaller piece.

Time Complexity:
O(n log n) due to sorting and convex hull computation (Andrew's monotone chain algorithm).
Space Complexity:
O(n) for storing the points and hull.

Techniques:
- Convex hull using Andrew's algorithm
- Geometric calculations involving circles, chords, and sectors
- Angles calculated using acos and trigonometric identities
*/

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <utility>
#include <vector>

#define fi first
#define se second
#define int long long
int n, r;
using namespace std;
typedef pair<int, int> point;
vector<point> hull, points;

// Cross product of three points to determine orientation
int cross(point a, point b, point c) {
  return (b.fi - a.fi) * (c.se - a.se) - (b.se - a.se) * (c.fi - a.fi);
}

// Compute convex hull using Andrew's monotone chain algorithm
void andrew() {
  sort(points.begin(), points.end());
  for (auto x : points) {
    while (hull.size() > 1 &&
           cross(hull[hull.size() - 2], hull.back(), x) <= 0) {
      hull.pop_back();
    }
    hull.push_back(x);
  }
  int k = hull.size();
  int sz = points.size();
  for (int i = sz - 2; i >= 0; i--) {
    auto x = points[i];
    while (hull.size() > k &&
           cross(hull[hull.size() - 2], hull.back(), x) <= 0) {
      hull.pop_back();
    }
    hull.push_back(x);
  }
  if (!hull.empty())
    hull.pop_back();
}

// Calculate area of the smaller piece when a line cuts the circle along a chord
double getarea(point a, point b) {
  double area = ((a.fi * b.se) - (a.se * b.fi)) / 2.0;
  double dist =
      sqrt((a.fi - b.fi) * (a.fi - b.fi) + (a.se - b.se) * (a.se - b.se));
  double h = area * 2 / dist; // Height of triangle (distance from origin to chord)
  double theta = acos(h / r) * 2; // Central angle of the sector
  double res = 0.5 * r * r * theta; // Area of the sector
  res -= h * r * sin(theta / 2); // Subtract triangle area to get segment area
  return res;
}

signed main() {
  cin >> n >> r;
  for (int i = 1; i <= n; i++) {
    int x, y;
    cin >> x >> y;
    points.emplace_back(x, y);
  }
  andrew();
  double ans = 0;
  int sz = hull.size();
  if (sz > 2) {
    for (int i = 0; i < sz; i++) {
      int j = (i + 1) % sz;
      ans = max(ans, getarea(hull[i], hull[j]));
    }
  } else {
    // If only 2 points, then the maximum area of smaller piece is half circle
    ans = acos(-1) * r * r / 2;
  }
  ans = min(ans, acos(-1) * r * r / 2); // Ensure the result does not exceed half area
  cout << fixed << setprecision(16) << ans << "\n";
  return 0;
}


// https://github.com/VaHiX/CodeForces/