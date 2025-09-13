/*
 * Problem URL : https://codeforces.com/contest/630/problem/O
 * Submit Date : 2025-09-09
 */

#include <cmath>
#include <cstdio>

#define pt(x, y)                                                               \
  printf("%.12f %.12f\n", x *co + y * si + px, -x * si + y * co + py);

int main() {
  int py, px, vx, vy, a, b, c, d;
  double si, co;
  scanf("%d%d%d%d%d%d%d%d", &px, &py, &vx, &vy, &a, &b, &c, &d);
  si = vx / hypot(vx, vy);
  co = vy / hypot(vx, vy);
  pt(0, b);
  pt((-a / 2.0), 0);
  pt((-c / 2.0), 0);
  pt((-c / 2.0), (-d));
  pt((c / 2.0), (-d));
  pt((c / 2.0), 0);
  pt((a / 2.0), 0);
}
/* Fri Feb 24 2023 22:54:38 GMT+0300 (Moscow Standard Time) */
