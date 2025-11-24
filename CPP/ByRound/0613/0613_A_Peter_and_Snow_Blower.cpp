// Problem: CF 613 A - Peter and Snow Blower
// https://codeforces.com/contest/613/problem/A

/*
 * Problem: Peter and Snow Blower
 * 
 * Purpose:
 *   This program computes the area of the region that will be cleared by a snow blower
 *   when tied to a point P and rotated around it. The snow blower is modeled as a polygon,
 *   and the cleared area is the ring between the maximum and minimum distance from P to the polygon.
 * 
 * Algorithm:
 *   - For each edge of the polygon, compute the distance from P to the two endpoints.
 *   - If the edge forms an obtuse angle with P, we ignore it (it does not contribute to the minimum distance).
 *   - Otherwise, compute the height of the triangle formed by P and the edge — this represents
 *     the shortest distance from P to the edge, which contributes to the inner radius.
 *   - Track the maximum and minimum distances from P to the polygon vertices and edges.
 *   - The result is the area of the circular ring: π * (R^2 - r^2)
 *     where R is the maximum distance and r is the minimum distance.
 * 
 * Time Complexity: O(n), where n is the number of vertices in the polygon.
 * Space Complexity: O(n), for storing the polygon vertices.
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define nmax 100010
#define PI 3.14159265358979323846
#define eps 1e-8
using namespace std;

struct point {
  int x, y;
};

int n;
point p, polygon[nmax];
double maxDist, minDist;

// Square function
double sqr(double x) { return x * x; }

// Euclidean distance between two points
double dist(const point a, const point b) {
  return sqrt(sqr(abs(a.x - b.x)) + sqr(abs(a.y - b.y)));
}

int main() {
  scanf("%d %d %d", &n, &p.x, &p.y);
  maxDist = 0;
  minDist = 1e18;

  // Read polygon vertices
  for (int i = 1; i <= n; i++)
    scanf("%d %d", &polygon[i].x, &polygon[i].y);

  // Connect last vertex to first to form a closed polygon
  polygon[0] = polygon[n];

  // Go through each edge
  for (int i = 0; i < n; i++) {
    double ap = dist(p, polygon[i]);     // Distance from P to vertex i
    double bp = dist(p, polygon[i + 1]); // Distance from P to vertex i+1
    double ab = dist(polygon[i], polygon[i + 1]); // Length of edge i-i+1

    // Update max and min distances to vertices
    maxDist = max(maxDist, ap);
    maxDist = max(maxDist, bp);
    minDist = min(minDist, ap);
    minDist = min(minDist, bp);

    // Check if the angle at the vertex is obtuse
    if (sqr(ap) + sqr(ab) < sqr(bp) || sqr(bp) + sqr(ab) < sqr(ap))
      continue;

    // Compute area of triangle using Heron's formula
    double p = (ap + bp + ab) / 2;
    double S = sqrt(p * (p - ap) * (p - bp) * (p - ab));
    double h = 2 * S / ab;  // Height from P to the edge

    // Update minimum distance to the edge (this is the inner radius)
    minDist = min(minDist, h);
  }

  // Output the area of the ring: π * (R^2 - r^2)
  printf("%.8f", PI * (sqr(maxDist) - sqr(minDist)));
  return 0;
}


// https://github.com/VaHiX/CodeForces/