/*
 * Problem URL : https://codeforces.com/problemset/problem/227/A
 * Submit Date : 2025-08-21
 */

#include <cstdio>

int main() {
  double xA, yA, xB, yB, xC, yC;
  scanf("%lf %lf\n%lf %lf\n%lf %lf\n", &xA, &yA, &xB, &yB, &xC, &yC);
  double result = (xB - xA) * (yC - yB) - (xC - xB) * (yB - yA);
  if (result == 0) {
    puts("TOWARDS");
  } else if (result < 0) {
    puts("RIGHT");
  } else {
    puts("LEFT");
  }
  return 0;
}
