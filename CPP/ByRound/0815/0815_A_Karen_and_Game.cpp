/*
 * Problem URL : https://codeforces.com/problemset/problem/815/A
 * Submit Date : 2025-08-19
 */

#include <bits/stdc++.h>
using namespace std;

int n, m, i, j, k, ds;
int g[105][105];
int d1[105], d2[105];

int main() {
  k = 1;
  ds = 0;
  d2[1] = 0;
  scanf("%d%d", &n, &m);
  for (j = 1; j <= m; j++) {
    scanf("%d", &g[1][j]);
    d2[j] = g[1][j] - g[1][1];
    if (d2[j] < ds)
      ds = d2[j];
  }
  for (i = 2; i <= n; i++)
    for (j = 1; j <= m; j++) {
      scanf("%d", &g[i][j]);
      if (k && (d2[j] != g[i][j] - g[i][1]))
        k = 0;
    }
  if (!k) {
    printf("-1\n");
    return 0;
  }
  for (j = 1; j <= m; j++)
    d2[j] -= ds;
  ds = 1000;
  for (i = 1; i <= n; i++) {
    d1[i] = g[i][1] - d2[1];
    if (d1[i] < ds)
      ds = d1[i];
  }
  if (n > m) {
    for (i = 1; i <= n; i++)
      d1[i] -= ds;
    for (j = 1; j <= m; j++)
      d2[j] += ds;
  }
  k = 0;
  for (i = 1; i <= n; i++)
    k += d1[i];
  for (j = 1; j <= m; j++)
    k += d2[j];
  printf("%d\n", k);
  for (i = 1; i <= n; i++)
    for (j = 1; j <= d1[i]; j++)
      printf("row %d\n", i);
  for (j = 1; j <= m; j++)
    for (i = 1; i <= d2[j]; i++)
      printf("col %d\n", j);
  return 0;
}

/*
5 3
1 0 2
1 0 2
1 0 2
2 1 3
1 0 2
*/
