/*
 * Problem URL : https://codeforces.com/problemset/problem/1801/A
 * Submit Date : 2025-08-21
 */

#include <cstdio>
int t, n, m;
signed main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d %d", &n, &m);
    printf("%d\n", n * m);
    for (int i = 1; i <= n; i++, puts(""))
      for (int j = 1; j <= m; j++)
        printf("%d ", (i << 9) + (j));
  }
}
