// Problem: CF 1826 F - Fading into Fog
// https://codeforces.com/contest/1826/problem/F

/*
Algorithm: Fading into Fog
Purpose: To find n hidden points on a 2D plane using projection queries on lines.
Approach:
1. Query two orthogonal lines (y-axis and x-axis) to get projections of all points.
2. Use the projections to infer the actual points by matching projected coordinates with possible real coordinates.
3. For each projection, compute the closest point from the known x-y coordinates.

Time Complexity: O(n^3) per test case due to nested loops in GetBestMatch function
Space Complexity: O(n) for storing points and coordinates
*/

#include <stdio.h>
#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;
typedef long long ll;
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pdd pair<double, double>
#define M 100

// Query function to get projections of points on line ax + by + c = 0
vector<pdd> Query(int n, double a, double b) {
  printf("? %lf %lf 0\n", a, b);
  fflush(stdout);
  vector<pdd> ans(n);
  for (int i = 0; i < n; ++i) {
    scanf("%lf%lf", &ans[i].first, &ans[i].second);
  }
  return ans;
}

// Get unique x-coordinates by projecting points onto y-axis (line 0*x + 1*y + 0 = 0)
set<double> GetXCoordinates(int n) {
  set<double> x_coordinates;
  for (auto [x, y] : Query(n, 0, 1)) {
    x_coordinates.insert(x);
  }
  return x_coordinates;
}

// Get unique y-coordinates by projecting points onto x-axis (line 1*x + 0*y + 0 = 0)
set<double> GetYCoordinates(int n) {
  set<double> y_coordinates;
  for (auto [x, y] : Query(n, 1, 0)) {
    y_coordinates.insert(y);
  }
  return y_coordinates;
}

// Calculate squared distance between two points
double Dist2(pdd &a, pdd &b) {
  return (a.first - b.first) * (a.first - b.first) +
         (a.second - b.second) * (a.second - b.second);
}

// Find best match point from x-y coordinates for a given expected projection
pdd GetBestMatch(set<double> &x_coordinates, set<double> &y_coordinates,
                 double m, pdd expected_projection) {
  double best_dist = 1e18;
  pdd best_match = {0, 0};
  for (double x : x_coordinates) {
    for (double y : y_coordinates) {
      // Calculate projection of point (x,y) onto line y = mx (or line m*x - y = 0)
      pdd actual_projection = {(x + m * y) / (1 + m * m),
                               (m * x + m * m * y) / (1 + m * m)};
      double dist = Dist2(actual_projection, expected_projection);
      if (dist < best_dist) {
        best_dist = dist;
        best_match = {x, y};
      }
    }
  }
  return best_match;
}

// Main solving function
vector<pdd> Solve() {
  int n;
  scanf("%d", &n);
  double m = 1.0 / (4 * M); // Slope for query line y = mx
  set<double> x_coordinates = GetXCoordinates(n);
  set<double> y_coordinates = GetYCoordinates(n);
  vector<pdd> expected_projections = Query(n, m, -1); // Line: m*x - y = 0
  vector<pdd> ans;
  for (pdd &expected_projection : expected_projections) {
    auto [x, y] =
        GetBestMatch(x_coordinates, y_coordinates, m, expected_projection);
    x_coordinates.erase(x), y_coordinates.erase(y); // Remove matched coordinates
    ans.push_back({x, y});
  }
  return ans;
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    vector<pdd> ans = Solve();
    printf("! ");
    for (auto [x, y] : ans) {
      printf("%lf %lf ", x, y);
    }
    printf("\n");
    fflush(stdout);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/