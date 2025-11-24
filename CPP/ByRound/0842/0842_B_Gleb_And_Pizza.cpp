// Problem: CF 842 B - Gleb And Pizza
// https://codeforces.com/contest/842/problem/B

/*
 * Problem: Gleb And Pizza
 * Purpose: Determine how many pieces of sausage lie entirely on the crust of a circular pizza.
 * 
 * Algorithm:
 * 1. The pizza is a circle of radius r centered at origin.
 * 2. The crust is the area between two concentric circles: 
 *    - Inner circle: radius (r - d)
 *    - Outer circle: radius r
 * 3. A piece of sausage (a circle) lies entirely on the crust if:
 *    - Its center is at distance from origin such that it touches or lies within the crust region.
 *    - Specifically, the entire circle must be within the crust but not inside the main pizza.
 * 4. For a sausage piece with center (x,y) and radius a:
 *    - It lies on crust if:
 *      - Distance from origin to center of sausage >= (r - d + a)
 *      - Distance from origin to center of sausage <= (r - a)
 * 
 * Time Complexity: O(n), where n is the number of sausage pieces.
 * Space Complexity: O(1), constant extra space used.
 */

#include <cstdio>
int main() {
  double r, d;
  scanf("%lf %lf", &r, &d);  // Read pizza radius and crust width
  long n;
  scanf("%ld", &n);  // Read number of sausage pieces
  long count(0);  // Counter for pieces on crust
  while (n--) {
    double x, y, a;
    scanf("%lf %lf %lf", &x, &y, &a);  // Read sausage center (x,y) and radius a
    // Check if sausage piece lies entirely on the crust
    count += (x * x + y * y >= (r - d + a) * (r - d + a)) &&
             (x * x + y * y <= (r - a) * (r - a));
  }
  printf("%ld\n", count);  // Print the number of pieces on crust
  return 0;
}


// https://github.com/VaHiX/CodeForces/