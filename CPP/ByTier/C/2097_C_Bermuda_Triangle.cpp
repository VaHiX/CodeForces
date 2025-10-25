// Problem: CF 2097 C - Bermuda Triangle
// https://codeforces.com/contest/2097/problem/C

/*
C. Bermuda Triangle
Purpose: Determine if an airplane inside a triangular region can escape by reaching a vertex,
         and count how many boundary hits occur before escaping.
Algorithms/Techniques:
  - Using reflection principle to unfold the triangle into a lattice of triangles.
  - Extended Euclidean algorithm for solving linear Diophantine equations.
  - Modular arithmetic and GCD usage.

Time Complexity: O(log(min(vx, vy))) per test case due to GCD calculation.
Space Complexity: O(1) — only using a constant amount of extra space.

Input Format:
  - n: size of triangle (vertices at (0,0), (0,n), (n,0))
  - x,y: initial position
  - vx, vy: velocity vector

Output:
  - Number of boundary hits before escaping, or -1 if never escaping.
*/

#include <stdlib.h>
#include <algorithm>
#include <iostream>

using namespace std;
using i64 = long long;

// Extended Euclidean algorithm to find gcd and coefficients such that ax + by = gcd(a,b)
i64 Gcd(i64 a, i64 b, i64 &x, i64 &y) {
  if (!b) {
    x = 1;
    y = 0;
    return a;
  }
  i64 g = Gcd(b, a % b, y, x); // recurse with swapped x,y
  y -= (a / b) * x;           // update y using recurrence relation
  return g;
}

void Solve() {
  i64 n, x, y, vx, vy;
  cin >> n >> x >> y >> vx >> vy;

  // Compute cross product of initial position and velocity vector to determine direction
  i64 d = x * vy - y * vx;
  if (d % n != 0) {
    cout << -1 << "\n"; // If not divisible by n, path does not hit a vertex
    return;
  }

  i64 dh = d / n; // Normalize to get relative position along the vector

  // Find gcd of velocity components for reducing vectors
  i64 u, v, g = Gcd(vy, vx, u, v);
  if (dh % g) {
    cout << -1 << "\n"; // If dh not divisible by g, no integer solution exists
    return;
  }

  // Multiply the solution from extended GCD with normalized factor
  i64 xx = u * (dh / g);
  i64 yy = -v * (dh / g);

  // Normalize vector components
  vx /= g;
  vy /= g;

  // Helper lambda for ceiling division
  auto cdiv = [](i64 a, i64 b) { return a > 0 ? (a + b - 1) / b : a / b; };

  // Calculate minimal time step to ensure we stay inside triangle (non-negativity)
  i64 w = max(cdiv(1 - xx, vx), cdiv(1 - yy, vy));
  
  // Adjust position to the first valid state that ensures positivity and entry into triangle
  xx += vx * w;
  yy += vy * w;

  // Formula derived from analysis of path through reflected triangle lattice
  cout << xx + yy - 2 + (xx + yy) / 2 + llabs(xx - yy) / 2 << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--) {
    Solve();
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/