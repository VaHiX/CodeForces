// Problem: CF 2138 F - Ode to the Bridge Builder
// https://codeforces.com/contest/2138/problem/F

/*
Purpose: This code solves the problem of constructing a specific point (p, q) on
a 2D plane using a series of geometric operations. Each operation involves
selecting two connected points, choosing a new point, and creating a triangle
with side lengths in [0.5, 1]. The goal is to reach the target point in at most
m operations.

Algorithms/Techniques:
- Geometric construction using triangle operations with constraints on side
lengths
- Multiple heuristics/solutions are tried to find a valid path to the target
- Point projection and circle-line intersection for precise point placement
- Bisection technique for distributing points along a line segment

Time Complexity: O(m) where m is the number of operations. The main loop is
limited by ceil(2 * sqrt(p^2 + q^2)), and each operation constructs points in
linear time.

Space Complexity: O(m) for storing the points and operations. Additional space
is used for intermediate geometric calculations but remains bounded by m.

*/
#include <bits/stdc++.h>
using namespace std;
// Type aliases and constants
typedef double db;
const db pi = acos(-1.0);
const int N = 1000005; // Maximum number of points/operations

// Test if a double is effectively zero (within epsilon)
inline int sgn(db x) {
  if (x < 1e-13 && x > -1e-13)
    return 0;
  if (x > 0)
    return 1;
  return -1;
}

// 2D point/vector structure with basic operations
struct point {
  db x, y;
  point(db _x = 0.0, db _y = 0.0) : x(_x), y(_y) {}
};

// Vector addition
point operator+(const point &p1, const point &p2) {
  return point(p1.x + p2.x, p1.y + p2.y);
}

// Vector subtraction
point operator-(const point &p1, const point &p2) {
  return point(p1.x - p2.x, p1.y - p2.y);
}

// Scalar multiplication
point operator*(db x, const point &p) { return point(x * p.x, x * p.y); }

// Point equality test (within epsilon)
bool operator==(point x, point y) {
  return sgn(x.x - y.x) == 0 && sgn(x.y - y.y) == 0;
}

// Dot product of two vectors
inline db dot(point p1, point p2) { return p1.x * p2.x + p1.y * p2.y; }

// Cross product (returns z-component)
inline db det(point p1, point p2) { return p1.x * p2.y - p2.x * p1.y; }

// Vector length/magnitude
inline db len(point p) { return sqrtl(1.0 * p.x * p.x + 1.0 * p.y * p.y); }

// Project point x onto line segment ya-yb
// Returns the point on line ya-yb closest to x
point project_point(point x, point ya, point yb) {
  point v = yb - ya; // Direction vector of line
  return ya + (dot(v, x - ya) / dot(v, v)) *
                  v; // ya + t*v where t optimizes distance
}

// Compute perpendicular distance from point x to line ya-yb
// Uses the fact that area = base * height to extract height (distance)
db distp(point x, point ya, point yb) {
  return fabs(det(ya - x, yb - x)) / len(yb - ya);
}

// Find intersection of unit circle centered at o with line la-lb
// First projects o onto the line, then extends perpendicular to line
// by the right amount (using Pythagorean theorem) to hit circle
point line_circle_intersec_point(point o, point la, point lb) {
  db dis = distp(o, la, lb), l;        // perpendicular distance from o to line
  point pj = project_point(o, la, lb); // projection of o onto line
  l = sqrt(1.0 - dis * dis); // length along line to intersection (Pythagoras)
  point ret = pj + (l / len(lb - la)) * (lb - la); // pj + l*unit_vector
  return ret;
}

tuple<int, int, int> ans[N];
point p[N], target;
int step;

bool check(int n) {
  set<pair<int, int>> st;
  st.insert({1, 2});
  if (n > step)
    return 0;
  db eps_len = 1e-8, eps_dis = 1e-4;
  int fl = 0;
  for (int i = 1; i <= n; i++) {
    auto [u, v, w] = ans[i];
    if (u > v)
      swap(u, v);
    if (st.find({u, v}) == st.end())
      return 0;
    if (len(p[u] - p[w]) < 0.5 - eps_len || len(p[u] - p[w]) > 1.0 + eps_len)
      return 0;
    if (len(p[v] - p[w]) < 0.5 - eps_len || len(p[v] - p[w]) > 1.0 + eps_len)
      return 0;
    st.insert({u, w});
    st.insert({v, w});
    if (len(p[w] - target) <= eps_dis)
      fl = 1;
  }
  return 1;
}

// First solution approach: Create path from origin (p[1])
// Divides path into segments and builds triangles towards target
int solve1a() {
  point dir = target - p[1];         // Direction vector from origin to target
  int split = ceil(len(dir) - 1e-9); // Number of segments needed
  int c = 2;                         // Current point counter
  for (int i = 1; i < split; i++) {
    ++c;
    p[c] = p[1] + (1.0 * i / split) * dir; // Point from origin
    ans[c - 2] = {c - 2, c - 1, c};        // Record triangle
    ++c;
    p[c] = p[2] + (1.0 * i / split) * dir; // Point from (1,0)
    ans[c - 2] = {c - 2, c - 1, c};        // Record triangle
  }
  ++c;
  p[c] = target;                  // Final point
  ans[c - 2] = {c - 2, c - 1, c}; // Last triangle
  if (check(c - 2))               // Verify construction
    return c - 2;                 // Return number of operations
  return 0;                       // Construction failed
}

// Alternative first solution: Create path from (1,0) (p[2])
// Similar to solve1a but starts from different base point
int solve1b() {
  point dir = target - p[2];         // Direction vector from (1,0) to target
  int split = ceil(len(dir) - 1e-9); // Number of segments needed
  int c = 2;                         // Current point counter
  for (int i = 1; i <= split; i++) {
    ++c;
    p[c] = p[1] + (1.0 * i / split) * dir; // Point from origin
    ans[c - 2] = {c - 2, c - 1, c};        // Record triangle
    ++c;
    p[c] = p[2] + (1.0 * i / split) * dir; // Point from (1,0)
    ans[c - 2] = {c - 2, c - 1, c};        // Record triangle
  }
  if (check(c - 2)) // Verify construction
    return c - 2;   // Return number of operations
  return 0;         // Construction failed
}

// Second solution approach: Use equilateral triangle and line-circle
// intersection
int solve2() {
  // Create equilateral triangle point at 60 degrees
  p[3] = point(sqrt(3.0) / 2, 0.5);
  // Find intersection of unit circle around p[3] with line from p[2] to target
  p[4] = line_circle_intersec_point(p[3], p[2], target);
  // If intersection is too far, move one unit towards target
  if (len(p[4] - p[2]) > 1)
    p[4] = p[2] + (1.0 / len(target - p[2])) * (target - p[2]);
  // Record initial triangles
  ans[1] = {1, 2, 3};
  ans[2] = {2, 3, 4};
  // Create path from p[4] to target
  point dir = target - p[4];
  int split = ceil(len(dir) - 1e-9);
  int c = 4;
  for (int i = 1; i <= split; i++) {
    ++c;
    p[c] = p[3] + (1.0 * i / split) * dir; // Point from triangle apex
    ans[c - 2] = {c - 2, c - 1, c};
    ++c;
    p[c] = p[4] + (1.0 * i / split) * dir; // Point from intersection
    ans[c - 2] = {c - 2, c - 1, c};
  }
  if (check(c - 2))
    return c - 2;
  return 0;
}

// Third solution approach variant A: Start from equilateral triangle
// Creates path from p[2] (1,0) to target using triangle at 60 degrees
int solve3a() {
  // Create equilateral triangle point at 60 degrees
  p[3] = point(0.5, sqrt(3.0) / 2);
  ans[1] = {1, 2, 3}; // Record initial triangle
  // Create path from p[2] to target
  point dir = target - p[2];
  int split = ceil(len(dir) - 1e-9);
  int c = 3;
  for (int i = 1; i < split; i++) {
    ++c;
    p[c] = p[2] + (1.0 * i / split) * dir; // Point from (1,0)
    ans[c - 2] = {c - 2, c - 1, c};
    ++c;
    p[c] = p[3] + (1.0 * i / split) * dir; // Point from triangle apex
    ans[c - 2] = {c - 2, c - 1, c};
  }
  ++c;
  p[c] = target; // Final point
  ans[c - 2] = {c - 2, c - 1, c};
  if (check(c - 2))
    return c - 2;
  return 0;
}

// Third solution approach variant B: Start from equilateral triangle
// Creates path from p[3] (triangle apex) to target
int solve3b() {
  // Create equilateral triangle point at 60 degrees
  p[3] = point(0.5, sqrt(3.0) / 2);
  ans[1] = {1, 2, 3}; // Record initial triangle
  // Create path from triangle apex to target
  point dir = target - p[3];
  int split = ceil(len(dir) - 1e-9);
  int c = 3;
  for (int i = 1; i <= split; i++) {
    ++c;
    p[c] = p[2] + (1.0 * i / split) * dir; // Point from (1,0)
    ans[c - 2] = {c - 2, c - 1, c};
    ++c;
    p[c] = p[3] + (1.0 * i / split) * dir; // Point from triangle apex
    ans[c - 2] = {c - 2, c - 1, c};
  }
  if (check(c - 2))
    return c - 2;
  return 0;
}

// Try all solution approaches until one succeeds
int solve() {
  // Try each approach in order of increasing complexity
  if (int res = solve1a()) // Direct path from origin
    return res;
  if (int res = solve1b()) // Direct path from (1,0)
    return res;
  if (int res = solve2()) // Equilateral triangle with line-circle intersection
    return res;
  if (int res = solve3a()) // Equilateral triangle path from (1,0)
    return res;
  if (int res = solve3b()) // Equilateral triangle path from apex
    return res;
  return 0; // No solution found (should not happen)
}

int main() {
  int TC;
  scanf("%d", &TC);   // Number of test cases
  p[1] = point(0, 0); // Origin point
  p[2] = point(1, 0); // Base point at (1,0)
  while (TC--) {
    int tx, ty; // Target coordinates
    scanf("%d %d %d", &tx, &ty, &step);
    // Maximum steps needed is proportional to distance to target
    step = ceil(2.0 * sqrt(1.0 * tx * tx + 1.0 * ty * ty));
    target = point(tx, ty); // Set target point
    int n = solve();        // Find solution
    assert(n > 0);          // Solution must exist
    printf("%d\n", n);      // Print number of operations
    // Print each operation: two base points and new point coordinates
    for (int i = 1; i <= n; i++) {
      auto [u, v, w] = ans[i];
      printf("%d %d %.12lf %.12lf\n", u, v, p[w].x, p[w].y);
    }
  }
  return 0;
}

// https://github.com/VaHiX/CodeForces/