/*
 * Problem URL : https://codeforces.com/contest/794/problem/B
 * Submit Date : 2025-09-04
 */

#include <cmath>
#include <cstdio>

int main() {

  double n, h;
  scanf("%lf %lf", &n, &h);
  for (long k = 1; k < n; k++) {
    printf("%.9lf ", h * sqrt(1.0 * k / n));
  }
  puts("");

  return 0;
}
