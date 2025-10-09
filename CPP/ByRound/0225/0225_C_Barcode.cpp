/*
 * Problem URL : https://codeforces.com/problemset/problem/225/C
 * Submit Date : 2025-08-21
 */

#include <bits/stdc++.h>
using namespace std;
int n, m, x, y, dp[2010][2], a[1010], b[1010];
char mp[1010][1010];
int main() {
  cin >> n >> m >> x >> y;
  for (int i = 1; i <= n; i++) {
    scanf("%s", mp[i] + 1);
    for (int j = 1; j <= m; j++) {
      if (mp[i][j] == '.')
        a[j]++;
      else
        b[j]++;
    }
  }
  memset(dp, 0x3f, sizeof dp);
  dp[0][0] = dp[0][1] = 0;
  for (int i = 1; i <= m; i++) {
    a[i] += a[i - 1];
    b[i] += b[i - 1];
  }
  for (int i = 1; i <= m; i++) {
    for (int j = x; i - j >= 0 && j <= y; j++) {
      dp[i][0] = min(dp[i][0], dp[i - j][1] + a[i] - a[i - j]);
      dp[i][1] = min(dp[i][1], dp[i - j][0] + b[i] - b[i - j]);
    }
  }
  cout << min(dp[m][1], dp[m][0]);
  return 0;
}