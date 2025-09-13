/*
 * Problem URL : https://codeforces.com/contest/2026/problem/B
 * Submit Date : 2025-09-10
 */

#include <stdio.h>
int t, n;
long long a[2222];
int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
      scanf("%lld", a + i);
    long long lb = 0, ub = 1e18;
    while (ub - lb > 1) {
      long long md = lb + (ub - lb) / 2;
      int zz = 0, x, i;
      for (x = 0, i = 0; i < n; ++i) {
        if (i && a[i] - a[i - 1] > md)
          zz += x, x = 0;
        x ^= 1;
      }
      zz += x;
      if (zz > 1)
        lb = md;
      else
        ub = md;
    }
    printf("%lld\n", ub);
  }
}