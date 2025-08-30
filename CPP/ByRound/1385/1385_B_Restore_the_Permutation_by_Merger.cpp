/*
 * Problem URL : https://codeforces.com/contest/1385/problem/B
 * Submit Date : 2025-08-25
 */

#include <cstdio>
int t, n, a[57], i, b;
main() {
  for (scanf("%d", &t); t--; puts(""))
    for (scanf("%d", &n), i = 0; i++ < 2 * n;)
      scanf("%d", &b), a[b] ? a[b] = 0 : (printf("%d ", b), ++a[b]);
}