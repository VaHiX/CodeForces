/*
 * Problem URL : https://codeforces.com/problemset/problem/2068/A
 * Submit Date : 2025-08-20
 */

#include <bits/stdc++.h>
using namespace std;
int g[55][55], n, m;
int main() {
  scanf("%d%d", &n, &m);
  puts("YES");
  printf("%d\n", 2 * m);
  for (int i = 1; i <= m; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    g[a][b] = 1;
    g[b][a] = 1 - g[a][b];
    printf("%d %d ", a, b);
    for (int j = 1; j <= n; j++) {
      if (j == a || j == b)
        continue;
      printf("%d ", j);
    }
    puts("");
    for (int j = n; j >= 1; j--) {
      if (j == a || j == b)
        continue;
      printf("%d ", j);
    }
    printf("%d %d\n", a, b);
  }
  return 0;
}