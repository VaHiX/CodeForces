/*
 * Problem URL : https://codeforces.com/problemset/problem/948/A
 * Submit Date : 2025-08-18
 */

#include <stdio.h>
char s[505][505];
int n, k, i, j;
main() {
  scanf("%d%d", &n, &k);
  for (i = 1; i <= n; i++)
    scanf("%s", s[i] + 1);
  for (i = 1; i <= n; i++) {
    for (j = 1; j <= k; j++) {
      if (s[i][j] == '.')
        s[i][j] = 'D';
      if (s[i][j] == 'S' && (s[i + 1][j] == 'W' || s[i - 1][j] == 'W' ||
                             s[i][j + 1] == 'W' || s[i][j - 1] == 'W')) {
        puts("No");
        return 0;
      }
    }
  }
  puts("Yes");
  for (i = 1; i <= n;)
    printf("%s\n", s[i++] + 1);
}
