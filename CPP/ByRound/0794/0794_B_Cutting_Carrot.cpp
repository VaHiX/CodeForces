// Problem: CF 794 B - Cutting Carrot
// https://codeforces.com/contest/794/problem/B

/*
 * Problem: Cutting Carrot
 * Purpose: Given an isosceles triangle (carrot) with base 1 and height h,
 *          cut it into n pieces of equal area using cuts parallel to the base.
 *          Output the distances from the apex where each cut should be made.
 *
 * Algorithm:
 *   - The area of the full triangle is (1 * h) / 2 = h / 2.
 *   - Each piece must have area h / (2 * n).
 *   - For a cut at height x from the apex, the smaller triangle formed has
 *     height x and base proportional to x (due to similarity of triangles).
 *     If full triangle has height h and base 1, then triangle of height x
 *     has base x / h.
 *   - Area of triangle up to height x = (1/2) * (x/h) * x = (x^2)/(2*h)
 *   - We want the area up to height x_i to be (i * h / (2 * n)) for i = 1..n-1
 *   - So (x_i^2)/(2*h) = (i * h)/(2 * n)
 *   - Solving: x_i^2 = (i * h^2) / n
 *   - Therefore: x_i = h * sqrt(i / n)
 *
 * Time Complexity: O(n) - single loop through n-1 cuts
 * Space Complexity: O(1) - only using a few variables
 */

#include <cmath>
#include <cstdio>
int main() {
  double n, h;
  scanf("%lf %lf", &n, &h);
  for (long k = 1; k < n; k++) {
    // Compute cut position using derived formula: x = h * sqrt(k/n)
    printf("%.9lf ", h * sqrt(1.0 * k / n));
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/CodeForces/