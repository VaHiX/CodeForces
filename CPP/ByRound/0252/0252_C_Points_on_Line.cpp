/*
 * Problem URL : https://codeforces.com/problemset/problem/252/C
 * Submit Date : 2025-08-19
 */

#include <cstdio>
#define R for (i = 1; i <= n; ++i)
int a[1 << 17], n, d, l = 1, i;
long long r;
main() {
  scanf("%d%d", &n, &d);
  R scanf("%d", &a[i]);
  R {
    while (a[i] - a[l] > d)
      ++l;
    r += (i - l) * 1ll * (i - l - 1) >> 1;
  }
  printf("%I64d", r);
}