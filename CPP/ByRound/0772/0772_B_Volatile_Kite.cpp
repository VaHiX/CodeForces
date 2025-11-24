// Problem: CF 772 B - Volatile Kite
// https://codeforces.com/contest/772/problem/B

/*
 * Problem: Volatile Kite
 * 
 * Purpose: Find the maximum distance D such that moving each vertex of a convex polygon 
 *          by at most D still keeps the polygon convex.
 * 
 * Algorithm: The key idea is to compute the minimum distance from each edge to the 
 *            opposite vertex. This minimum distance (divided by 2) gives the maximum 
 *            allowable movement. For a convex polygon, the minimum such distance 
 *            corresponds to the smallest distance from a vertex to the line formed 
 *            by the two adjacent edges.
 * 
 * Time Complexity: O(n), where n is the number of vertices. Each vertex is processed once.
 * Space Complexity: O(n), to store the polygon vertices.
 * 
 * Techniques: 
 *  - Use of cross product to compute distance from point to line
 *  - Iterate through all edges and compute corresponding distances
 */

#include <cmath>
#include <cstdio>
#include <vector>

struct point {
  double x, y;
};

// Function to compute the distance from point p2 to the line formed by p1 and p3
double dist(point p1, point p2, point p3) {
  double a = p3.y - p1.y;
  double b = p1.x - p3.x;
  double c = -b * p3.y - p3.x * a;
  double r = (a * p2.x + b * p2.y + c) / sqrt(a * a + b * b);
  r = (r > 0) ? r : -r;
  return r;
}

int main() {
  long n;
  scanf("%ld", &n);
  std::vector<point> v(n);
  for (long p = 0; p < n; p++) {
    scanf("%lf %lf", &v[p].x, &v[p].y);
  }
  
  // Initialize the answer with the distance from the first edge to the third vertex
  double ans = dist(v[0], v[1], v[2]);
  
  // Iterate over all edges to find the minimum distance
  for (int p = 1; p < n; p++) {
    double cand = dist(v[p], v[(p + 1) % n], v[(p + 2) % n]);
    ans = (ans < cand) ? ans : cand;
  }
  
  // The maximum allowable distance D is half of the minimum distance found
  printf("%.10lf", ans / 2);
}


// https://github.com/VaHiX/CodeForces/