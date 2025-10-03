/*
 * Problem URL : https://codeforces.com/problemset/problem/108/D
 * Submit Date : 2025-08-13
 */

#include <cstdio>
int c[1001], n, h, m, t;
int main() {
  scanf("%d%d%d", &n, &m, &h);
  for (int i = 1; i <= m; i++)
    t += scanf("%d", c + i) - 1 + c[i];
  if (t < n) {
    printf("-1");
    return 0;
  }
  n--;
  c[h]--;
  t--;
  double r = 1;
  for (int i = 0; i < c[h]; i++)
    r *= 1. * (t - n - i) / (t - i);
  printf("%.9f", 1 - r);
}