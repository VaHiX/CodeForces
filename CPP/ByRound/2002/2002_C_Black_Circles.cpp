// Problem: CF 2002 C - Black Circles
// https://codeforces.com/contest/2002/problem/C

/*
C. Black Circles
Problem Description:
We are given n circles on a 2D plane, each with center (xi, yi) and initially radius 0.
The radii increase at a rate of 1 unit per second.
We start at (xs, ys) and must reach (xt, yt) without touching any circle's circumference.
Movement speed is limited to 1 unit per second.

Algorithm:
- For each test case, compute the squared distance from the start point to target point.
- For each circle, compute its squared distance to the target.
- If any circle's distance to target is less than or equal to the start-to-target distance,
  then it's impossible to reach the target without touching a circle (because we'd be
  too close to the circle and could touch it as it expands).
- Optimization: Check only the circles' impact on the exit point, not the whole path.

Time Complexity: O(n) per test case
Space Complexity: O(n) for storing circle centers
*/
#include <cstdio>
#include <vector>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    std::vector<ll> x(n), y(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld %lld", &x[p], &y[p]);
    }
    ll xs, ys, xt, yt;
    scanf("%lld %lld %lld %lld", &xs, &ys, &xt, &yt);
    
    // Compute squared distance from start to target
    ll dst = (xs - xt) * (xs - xt) + (ys - yt) * (ys - yt);
    bool possible(true);  // Assume it's possible initially
    
    for (long p = 0; possible && p < n; p++) {
      // Compute squared distance from current circle to target
      ll cdt = (x[p] - xt) * (x[p] - xt) + (y[p] - yt) * (y[p] - yt);
      
      // If this circle is closer to the target than our path can avoid it,
      // then we cannot reach the target safely.
      if (cdt <= dst) {
        possible = false;
      }
    }
    
    puts(possible ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/