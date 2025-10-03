/*
 * Problem URL : https://codeforces.com/contest/630/problem/P
 * Submit Date : 2025-09-09
 */

#include <cmath>
#include <cstdio>
int main() {
  double n, r;
  scanf("%lf%lf", &n, &r);
  double a = atan(1) * 2 / n;
  printf("%.10f\n", r * r * n * sin(2 * a) * sin(a) / sin((n * 2 - 3) * a));
}