// Problem: CF 2073 M - Can You Reach There?
// https://codeforces.com/contest/2073/problem/M

/*
 * Problem: Can You Reach There?
 *
 * Purpose: Determine if it's possible to reach a target point from a starting point 
 *          using a specific movement rule involving marked points on a 2D plane.
 *
 * Algorithm:
 *   - Preprocess the configuration of marked points into geometric dimensions (0, 1, or 2).
 *   - For dimension 0 (a single point), only check if target is farther than start.
 *   - For dimension 1 (collinear points), compute the direction vector to allow for step calculations.
 *   - For dimension 2 (non-collinear points), any valid configuration allows movement in all directions.
 *
 * Time Complexity: O(n + Q * sqrt(n))
 * Space Complexity: O(n)
 */

#include <assert.h>
#include <bits/std_abs.h>
#include <cmath>
#include <iostream>
#include <stdio.h>
using namespace std;
typedef long long ll;
const int maxn = 200111;
#define FF first
#define SS second
#define PB push_back
#define MP make_pair

struct point {
  ll x, y;
  point(ll X = 0, ll Y = 0) : x(X), y(Y) {}
  point operator+(const point &t) const { return point(x + t.x, y + t.y); }
  point operator-(const point &t) const { return point(x - t.x, y - t.y); }
  point operator*(const ll &t) const { return point(x * t, y * t); }
  point operator/(const ll &t) const { return point(x / t, y / t); }
  ll det(const point &t) const { return x * t.y - y * t.x; }    // Cross product
  double detd(const point &t) const { return 1.0 * x * t.y - 1.0 * y * t.x; }
  ll len2() const { return x * x + y * y; }                    // Squared length
  void in() { scanf("%lld%lld", &x, &y); }
  void out() { cout << x << "," << y << endl; }
};

int n, Q;
point a[maxn];               // Marked points array
int dim;                     // Geometric dimension: 0 (single point), 1 (collinear), 2 (general)
point dir;                   // Direction vector for collinear case

// Integer square root calculation
ll sqrtl(ll x) {
  ll y = sqrt(x);
  while ((y + 1) * (y + 1) <= x)
    y++;
  while (y > 0 && (y - 1) * (y - 1) >= x)
    y--;
  return y;
}

// Process a query to determine if it's possible to reach from p to q
void solve_query() {
  point p, q;          // Start and target points
  p.in();              // Read start coordinates
  q.in();              // Read target coordinates

  if (dim == 0) {      // Point case - only direct distance matters
    if ((p - a[1]).len2() < (q - a[1]).len2()) {
      puts("no");      // Target is closer, impossible to get there by steps
      return;
    }
    if ((p - a[1]).len2() > 0 && (p - a[1]).det(q - a[1]) != 0) {  
      puts("no");      // Points not aligned with origin, invalid path
      return;
    }
    puts("yes");
  } else if (dim == 2) {
    puts("yes");       // General case allows movement to anywhere
  } else {
    assert(dim == 1);
    ll pd = abs((a[2] - a[1]).det(p - a[1])); // Perpendicular distance from p to line
    ll qd = abs((a[2] - a[1]).det(q - a[1])); // Perpendicular distance from q to line

    if (pd < qd) {
      puts("no");      // Target is further from line than initial point, impossible
    } else if (pd == 0 || qd < pd) {
      puts("yes");     // Target is either on line or closer, reachable
    } else {
      assert(pd == qd && pd > 0);
      for (int i = 0; i < 2; i++) {
        assert(dir.det(q - a[1]) != 0);       // Ensure non-zero cross product for projection
        ll t = (p - a[1]).det(q - a[1]) / -dir.det(q - a[1]); // Compute projection parameter
        if ((p + dir * t - q).len2() == 0) {  // Check if projected point equals target
          puts("yes");
          return;
        }
        p = a[1] + a[1] - p;                   // Reflect p about center (a[1]) to test other projection
      }
      puts("no");                              // Not reachable through any reflections
    }
  }
}

ll gcd(ll x, ll y) { return y == 0 ? x : gcd(y, x % y); }

int main() {
  scanf("%d%d", &n, &Q);
  for (int i = 1; i <= n; i++) {
    a[i].in();     // Read all marked points
  }

  dim = n >= 2;              // Determine dimension based on number of points

  if (n >= 3) {              // If at least three points, check collinearity
    for (int i = 3; i <= n; i++) {
      if ((a[2] - a[1]).det(a[i] - a[1]) != 0) {
        dim = 2;       // Points not collinear -> full-dimensional case (dim=2)
        break;
      }
    }
  }

  if (dim == 1) {            // For collinear points, compute direction vector
    ll g = 0;
    for (int i = 2; i <= n; i++) {
      g = gcd(g, (a[i] - a[1]).len2()); // Calculate gcd of squared distances to normalize
    }
    assert(g != 0);
    ll multi = (a[2] - a[1]).len2() / g;
    ll sm = sqrtl(multi);   // Take integer square root
    assert(sm * sm == multi);
    dir = (a[2] - a[1]) / sm;  // Normalize direction vector
    assert(dir.len2() > 0);
  }

  for (int i = 1; i <= Q; i++) {
    solve_query();      // Answer each query
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/