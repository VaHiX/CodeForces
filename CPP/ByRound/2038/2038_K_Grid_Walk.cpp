/*
 * Problem URL : https://codeforces.com/problemset/problem/2038/K
 * Submit Date : 2025-08-14
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 150;
int n, a, b, x, y;
ll sum, dp[N][N];
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n >> a >> b;
  for (x = n; x > 0; --x)
    if (__gcd(x, a) == 1)
      break;
  for (y = n; y > 0; --y)
    if (__gcd(y, b) == 1)
      break;
  for (int i = 1; i <= x; ++i)
    sum += __gcd(i, a);
  for (int i = 1; i <= y; ++i)
    sum += __gcd(i, b);
  memset(dp, 0x3f3f, sizeof dp);
  dp[1][1] = sum + x + y - 2;
  for (int i = x; i <= n; ++i)
    for (int j = y; j <= n; ++j) {
      if (i == x && j == y)
        continue;
      dp[i - x + 1][j - y + 1] =
          min(dp[i - x][j - y + 1], dp[i - x + 1][j - y]);
      dp[i - x + 1][j - y + 1] += __gcd(i, a) + __gcd(j, b);
    }
  cout << dp[n - x + 1][n - y + 1];
  return 0;
}