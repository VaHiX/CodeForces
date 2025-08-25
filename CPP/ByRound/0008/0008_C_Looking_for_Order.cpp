/*
 * Problem URL : https://codeforces.com/contest/8/problem/C
 * Submit Date : 2025-08-25
 */

#include <bits/stdc++.h>
using namespace std;
const int inf = 1007483647;
int n, m, xx, yy, x[33], y[33], d[33][33], dp[1 << 25], pre[1 << 25];
int main() {
  scanf("%d%d%d", &xx, &yy, &n), m = (1 << n) - 1;
  for (int i = 0; i < n; ++i)
    scanf("%d%d", x + i, y + i);
  x[n] = xx, y[n] = yy;
  for (int i = 0; i <= n; ++i)
    for (int j = 0; j <= n; ++j)
      d[i][j] = (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
  for (int i = 1; i < (1 << 24); ++i)
    dp[i] = inf;
  for (int i = 0; i < (1 << n); ++i)
    if (dp[i] != inf)
      for (int j = 0; j < n; ++j)
        if (!(i & (1 << j))) {
          int t = i | (1 << j), l = dp[i] + d[n][j] + d[j][n], p;
          if (dp[t] > l)
            dp[t] = l, pre[t] = i;
          for (int k = j + 1; k < n; ++k)
            if (!(t & (1 << k))) {
              p = t | (1 << k), l = dp[i] + d[n][j] + d[j][k] + d[k][n];
              if (dp[p] > l)
                dp[p] = l, pre[p] = i;
            }
          break;
        }
  printf("%d\n0", dp[m]);
  for (; m; m = pre[m]) {
    for (int i = 0; i < n; ++i)
      if ((m ^ pre[m]) & (1 << i))
        printf(" %d", i + 1);
    printf(" 0");
  }
}