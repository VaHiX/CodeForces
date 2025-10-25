/*
 * Problem URL : https://codeforces.com/contest/588/problem/A
 * Submit Date : 2025-09-04
 */

#include <stdio.h>
int n, a, p, t, pp;
int main() {
  scanf("%d%d%d", &n, &a, &p);
  t += a * p;
  pp = p;
  for (; --n;) {
    scanf("%d%d", &a, &p);
    if (p < pp)
      pp = p;
    t += a * pp;
  }
  printf("%d\n", t);
}