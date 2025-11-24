// Problem: CF 498 A - Crazy Town
// https://codeforces.com/contest/498/problem/A

/*
Algorithm: 
- The problem is about determining the minimum number of steps to move from home to university in a plane divided by lines (roads).
- Each line divides the plane into two half-planes.
- For each line, we compute the sign of the expression (a*x + b*y + c) for both home and university coordinates.
- If the signs differ, the line separates home and university, meaning we need to cross it (one step).
- The number of such separating lines is the minimum number of steps.

Time Complexity: O(n), where n is the number of roads.
Space Complexity: O(1), only a few variables are used.
*/

#include <cstdio>
int main() {
  double hx, hy;
  scanf("%lf %lf\n", &hx, &hy);
  double ux, uy;
  scanf("%lf %lf\n", &ux, &uy);
  int n;
  scanf("%d\n", &n);
  int steps(0);
  while (n--) {
    double a, b, c;
    scanf("%lf %lf %lf\n", &a, &b, &c);
    // Check if the home and university are on opposite sides of the line
    if ((a * hx + b * hy + c) * (a * ux + b * uy + c) < 0) {
      ++steps;
    }
  }
  printf("%d\n", steps);
  return 0;
}


// https://github.com/VaHiX/CodeForces/