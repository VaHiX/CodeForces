/*
 * Problem URL : https://codeforces.com/problemset/problem/467/C
 * Submit Date : 2025-08-20
 */

#include <iostream>
long long a[5003], dp[5003][2];
int main() {
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 1, x; i <= n; ++i)
    scanf("%d", &x), a[i] = a[i - 1] + x;
  for (int i = 1; i <= k; ++i)
    for (int j = i * m; j <= n; ++j)
      dp[j][i & 1] =
          std::max(dp[j - 1][i & 1], dp[j - m][i & 1 ^ 1] + a[j] - a[j - m]);
  printf("%lld\n", dp[n][k & 1]);
}