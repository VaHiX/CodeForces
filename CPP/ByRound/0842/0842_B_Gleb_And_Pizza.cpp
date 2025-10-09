/*
 * Problem URL : https://codeforces.com/problemset/problem/842/B
 * Submit Date : 2025-08-20
 */

#include <cstdio>

int main() {

  double r, d;
  scanf("%lf %lf", &r, &d);
  long n;
  scanf("%ld", &n);
  long count(0);
  while (n--) {
    double x, y, a;
    scanf("%lf %lf %lf", &x, &y, &a);
    count += (x * x + y * y >= (r - d + a) * (r - d + a)) &&
             (x * x + y * y <= (r - a) * (r - a));
  }

  printf("%ld\n", count);

  return 0;
}
