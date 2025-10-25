// Problem: CF 1912 I - Innovative Washing Machine
// https://codeforces.com/contest/1912/problem/I

/*
 * Problem: Innovative Washing Machine
 * Algorithm: 
 *   - Use rotating convex polygon to simulate water distribution.
 *   - For each moment, calculate the area of water and related pressure imbalance.
 *   - Precompute angles for edges and water surface positions for all possible rotations.
 *   - Apply sweep line technique with angular events to compute expectation.
 *
 * Time Complexity: O(n log n) per test case due to sorting events
 * Space Complexity: O(n) for storing angular events and auxiliary arrays
 */

#include <bits/std_abs.h>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <utility>

using namespace std;
typedef long long LL;
typedef double DB;
const int N = 222222;
const DB PI = acos(-1.0);
struct node {
  int x, y;
  node(int X = 0, int Y = 0) { x = X, y = Y; }
} a[N];
node operator-(node a, node b) { return node(a.x - b.x, a.y - b.y); }
LL G(node a, node b) { return (LL)a.x * b.y - (LL)a.y * b.x; }
LL S(int i, int j, int k) { return abs(G(a[j] - a[i], a[k] - a[i])); }
int n, m;
LL s;
DB f[N], g[N], h[N];
pair<DB, int> e[N * 3];
int main() {
  int T, i, j, k, o;
  LL t, w, x, y, z;
  DB p, q, r;
  node c, d;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%lld", &n, &s);
    for (i = 0; i < n; i++)
      scanf("%d%d", &a[i].x, &a[i].y);
    s *= 2;
    i = 0, j = 1, t = 0;
    while (1) {
      while (1) {
        w = S(i, j, (j + 1) % n); // Compute area of triangle formed by i,j,(j+1)
        if (t + w <= s) // If adding the new triangle doesn't exceed water volume
          t += w, j = (j + 1) % n; // Add triangle area and advance j
        else
          break;
      }
      w = S(i, j, (j + 1) % n); // Area of next triangle for interpolation
      r = (DB)(s - t) / w; // Fractional position along the edge
      c = a[j] - a[i]; // Vector from i to j
      d = a[(j + 1) % n] - a[j]; // Vector from j to j+1
      p = c.x + r * d.x; // Interpolated x coordinate on line segment
      q = c.y + r * d.y; // Interpolated y coordinate on line segment
      f[i] = atan2(q, p); // Compute angle of intersection point
      if (i == n - 1) // If we process all vertices
        break;
      t -= S(i, i + 1, j); // Subtract area of triangle formed by i,i+1,j
      i++; // Move to next vertex
    }
    i = n - 1, j = n - 2, t = 0;
    while (1) {
      while (1) {
        w = S(i, j, (j + n - 1) % n); // Area of triangle on backwards direction
        if (t + w <= s)
          t += w, j = (j + n - 1) % n; // Advance backward
        else
          break;
      }
      w = S(i, j, (j + n - 1) % n); // Area again for interpolation
      r = (DB)(s - t) / w; // Fractional position
      c = a[j] - a[i]; // Vector from i to j
      d = a[(j + n - 1) % n] - a[j]; // Vector from j to previous vertex
      p = c.x + r * d.x;
      q = c.y + r * d.y;
      g[i] = atan2(-q, -p); // Angle computed with opposite sign for backwards sweep
      if (i == 0)
        break;
      t -= S(i, i - 1, j);
      i--;
    }
    for (i = 0; i < n; i++) {
      c = a[i] - a[(i + n - 1) % n]; // Vector from previous to current vertex
      h[i] = atan2(c.y, c.x); // Angle of the edge
    }
    m = 0;
    for (i = 0; i < n; i++) {
      e[++m] = make_pair(f[i], 1); // Add entry point of current water line
      e[++m] = make_pair(g[i], 2); // Add exit point of current water line
      e[++m] = make_pair(h[i], 3); // Add edge angle
    }
    sort(e + 1, e + m + 1); // Sort angles to perform angular sweep
    e[0] = make_pair(-PI, 0); // Initialize start event
    e[m + 1] = make_pair(PI, 0); // Initialize end event
    
    for (i = 0; i < n; i++)
      if (h[i] > h[(i + 1) % n]) // Find starting edge that crosses boundary
        k = i;
    
    for (i = k; f[i] < g[i]; i = (i + n - 1) % n) // Find the first valid start index
      ;
    i = (i + 1) % n;
    for (j = k; f[j] < g[j]; j = (j + 1) % n) // Find the second valid index
      ;
    j = (j + n - 1) % n;
    
    z = 0, x = 0, y = 0; // Initialize variables for tracking area and centroid
    for (o = i; o != (j + 1) % n; o = (o + 1) % n)
      z++, x += a[o].x, y += a[o].y; // Initialize area and sum of coordinates

    r = 0;
    for (o = 1; o <= m + 1; o++) { // Sweep through events
      p = e[o - 1].first;
      q = e[o].first;
      
      // Add contribution from angular sector to expectation
      r += (x - z * a[k].x) * (cos(q) - cos(p)) / z;
      r += (y - z * a[k].y) * (sin(q) - sin(p)) / z;
      
      if (e[o].second == 1) { // Handle entry event
        z--, x -= a[i].x, y -= a[i].y; // Adjust count and centroid
        i = (i + 1) % n; // Move to next entry point
      }
      if (e[o].second == 2) { // Handle exit event
        j = (j + 1) % n; // Move to next exit point
        z++, x += a[j].x, y += a[j].y; // Adjust count and centroid
      }
      if (e[o].second == 3) { // Handle edge angle event
        k = (k + 1) % n; // Move to next edge
      }
    }
    printf("%.12lf\n", r / PI / 2); // Output final expected value
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/