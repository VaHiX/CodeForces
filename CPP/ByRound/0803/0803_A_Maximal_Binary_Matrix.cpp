/*
 * Problem URL : https://codeforces.com/contest/803/problem/A
 * Submit Date : 2025-09-04
 */

#include <cstdio>
int i, j, n, k, a[101][101];
int main() {
  scanf("%d%d", &n, &k);
  if (n * n < k)
    return puts("-1");
  for (i = 1; i <= n && k; ++i) {
    if (a[i][i] = 1, !--k)
      break;
    for (j = i + 1; j <= n && k > 1; ++j)
      a[i][j] = a[j][i] = 1, k -= 2;
  }
  for (i = 1; i <= n; ++i, puts(""))
    for (j = 1; j <= n; ++j)
      printf("%d ", a[i][j]);
}