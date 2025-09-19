/*
 * Problem URL : https://codeforces.com/contest/1100/problem/C
 * Submit Date : 2025-08-28
 */

#include <cmath>
#include <cstdio>

#define PI 3.14159265

int main() {

  long n;
  double r;
  scanf("%ld %lf", &n, &r);
  printf("%.8lf\n", r * sin(PI / n) / (1 - sin(PI / n)));

  return 0;
}
