/*
 * Problem URL : https://codeforces.com/problemset/problem/2075/D
 * Submit Date : 2025-08-22
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 57, M = 15;
const int inf = 0x3f3f3f3f;
int t;
int dp[N + 1][N + 1];
LL x, y;
void solve() {
  scanf("%lld%lld", &x, &y);
  int ans = inf;
  for (int i = 0; i <= N; i++)
    for (int j = 0; j <= N; j++)
      if ((x >> i) == (y >> j))
        ans = min(ans, dp[i][j]);
  printf("%d\n", ans);
}
int main() {
  memset(dp, 0x3f, sizeof(dp));
  dp[0][0] = 0;
  for (int i = 1; i <= M; i++)
    for (int j = N; j >= 0; j--)
      for (int k = N; k >= 0; k--) {
        if (j >= i)
          dp[j][k] = min(dp[j][k], dp[j - i][k] + (1 << i));
        if (k >= i)
          dp[j][k] = min(dp[j][k], dp[j][k - i] + (1 << i));
      }
  scanf("%d", &t);
  while (t--)
    solve();
  return 0;
}
