/*
 * Problem URL : https://codeforces.com/contest/1866/problem/J
 * Submit Date : 2025-09-07
 */

#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 410;
const ll INF = 1e16;
ll dp[N][N], g[N][2];
int n, x, y;
int a[N], b[N];
int main() {
  scanf("%d%d%d", &n, &x, &y);
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]);
  int m = 1;
  b[1] = 1;
  for (int i = 2; i <= n; i++)
    if (a[i] == a[m]) {
      b[m]++;
    } else {
      a[++m] = a[i];
      b[m] = 1;
    }
  n = m;
  for (int i = n; i >= 1; i--) {
    dp[i][i] = x;
    for (int j = i; j <= n; j++)
      g[j][0] = g[j][1] = INF;
    g[i][0] = 1ll * b[i] * y;
    g[i][1] = 2ll * b[i] * y;
    for (int j = i + 1; j <= n; j++)
      dp[i][j] = dp[i + 1][j] + x;
    for (int j = i + 1; j <= n; j++)
      if (a[j] == a[i]) {
        ll s = INF;
        for (int k = i; k < j; k++)
          if (a[k] == a[i]) {
            g[j][0] = min(g[k][0] + 1ll * b[j] * y + dp[k + 1][j - 1], g[j][0]);
            g[j][1] = min(g[k][1] + 2ll * b[j] * y + dp[k + 1][j - 1], g[j][1]);
            s = min(s, g[j][0] + x);
            s = min(s, g[k][1] + dp[k + 1][j - 1] + x);
          }
        dp[i][j] = min(dp[i][j], s);
        for (int k = j + 1; k <= n; k++)
          dp[i][k] = min(dp[i][k], dp[i][j] + dp[j + 1][k]);
      }
  }
  printf("%lld\n", dp[1][n]);
}