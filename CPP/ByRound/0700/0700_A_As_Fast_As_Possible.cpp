/*
 * Problem URL : https://codeforces.com/contest/700/problem/A
 * Submit Date : 2025-09-02
 */



#include <cmath>
#include <cstdio>

int main() {

  double n, l, v1, v2, k;
  scanf("%lf%lf%lf%lf%lf", &n, &l, &v1, &v2, &k);
  double m = floor((n + k - 1) / k);
  double speed = m * v2 - 1.0 * (m - 1) * v2 * (v2 - v1) / (v2 + v1);
  double t = l / speed;
  double time = t + 1.0 * (l - v2 * t) / v1;
  printf("%.8lf\n", time);

  return 0;
}
