// Problem: CF 630 P - Area of a Star
// https://codeforces.com/contest/630/problem/P

/*
 * Purpose: Calculate the area of a star figure with n corners (where n is prime)
 *          constructed by connecting each point on a circle to two maximally
 *          distant points.
 *
 * Algorithm: 
 *   - The star is formed by n points on a circle of radius r, equally spaced.
 *   - Each point connects to two maximally distant points (i.e., skipping (n-3)/2 points).
 *   - The area is derived from the formula involving trigonometric functions.
 *   - Key formula: Area = n * r^2 * sin(2*a) * sin(a) / sin((2*n - 3)*a)
 *     where a = pi / n (angle between adjacent points).
 *
 * Time Complexity: O(1) - constant time operations using trigonometric functions.
 * Space Complexity: O(1) - only a few variables are used.
 */

#include <cmath>
#include <cstdio>
int main() {
  double n, r;
  scanf("%lf%lf", &n, &r);
  double a = atan(1) * 2 / n;  // Compute angle a = pi / n
  printf("%.10f\n", r * r * n * sin(2 * a) * sin(a) / sin((n * 2 - 3) * a));  // Apply star area formula
}


// https://github.com/VaHiX/CodeForces/