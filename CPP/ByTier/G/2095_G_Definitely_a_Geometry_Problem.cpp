// Problem: CF 2095 G - Definitely a Geometry Problem
// https://codeforces.com/contest/2095/problem/G

/*
G. Definitely a Geometry Problem
Algorithms/Techniques: Sorting, Sliding Window
Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for storing the slime positions

Megumin wants to kill at least k slimes with a single explosion spell.
The cost of the spell is proportional to the area of the circle used,
which is π * r^2. We want to minimize this area.

Approach:
1. Sort all slimes by their x-coordinate.
2. Use a sliding window technique to find the smallest rectangle that contains at least k slimes.
3. For each such valid window, compute the minimum enclosing circle's area.
4. The key insight is that for any set of points, we can always construct the smallest enclosing circle
   such that at least one point lies on the boundary of the circle.
5. However, in this problem, with sorted x-positions, we look at the minimal square or rectangle,
   and compute its diagonal length to get a minimum radius.

But even simpler: after sorting:
- For each window of size k, compute the bounding square (min/max x/y).
- The minimal enclosing circle for that window has diameter equal to max(dx, dy),
  thus radius = max(dx, dy)/2.
- Therefore, minimizing the area means minimizing the squared diameter.

We optimize over all valid windows of k consecutive slimes in the sorted list,
and for each window compute:
- dx = rightmost_x - leftmost_x
- dy = topmost_y - bottommost_y
- Then square of minimal radius = max(dx^2, dy^2) / 4
*/

#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

typedef long long ll;
int main() {
  const double PI = 3.1415926535;
  long n, k;
  scanf("%ld %ld", &n, &k);
  std::vector<std::pair<double, double>> v(n);
  for (long p = 0; p < n; p++) {
    double x, y;
    scanf("%lf %lf", &x, &y);
    v[p] = std::make_pair(x, y); // Store slime coordinates
  }
  sort(v.begin(), v.end()); // Sort slimes by x-coordinate to enable sliding window

  double md = 1e30; // Initialize minimum squared distance to a large value

  // Sliding window over k consecutive points
  for (long p = k - 1; p < n; p++) {
    double dx = (v[p].first - v[p - k + 1].first); // Width of the window in x-direction
    double dy = (v[p].second - v[p - k + 1].second); // Height of the window in y-direction
    double dsq = dx * dx + dy * dy; // Squared diagonal length of enclosing square
    md = (md < dsq ? md : dsq); // Keep track of minimum
  }

  printf("%.8lf\n", PI * md / 4); // Output the area of minimal circle using π * r^2
}


// https://github.com/VaHiX/codeForces/