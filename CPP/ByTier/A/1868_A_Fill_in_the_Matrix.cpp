/*
 * Problem URL : https://codeforces.com/problemset/problem/1868/A
 * Submit Date : 2025-08-21
 */

#include <bits/stdc++.h>
using namespace std;
int n, m, i, j, T_T;
int main() {
  for (scanf("%d", &T_T); T_T--;) {
    scanf("%d%d", &n, &m);
    printf("%d\n", m > 1 ? min(n + 1, m) : 0);
    for (i = 1; i <= n; ++i, puts(""))
      for (j = 1; j <= m; ++j)
        printf("%d ", (min(i, m - 1) + j) % m);
  }
}