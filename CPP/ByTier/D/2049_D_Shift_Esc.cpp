/*
 * Problem URL : https://codeforces.com/problemset/submit
 * Submit Date : 2025-08-24
 */

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
constexpr int N = 2e2 + 5;
constexpr long long MAX_LONG = 1e18;
long long dp[N][N], f[N][N];
int a[N];
void work() {
  int n, m, K;
  scanf("%d%d%d", &n, &m, &K);
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < m; j++)
      scanf("%d", &a[j]);
    for (int j = 0; j < m; j++) {
      long long mi = 1e18;
      for (int k = 0; k < m; k++) {
        f[k][j] = min(j ? f[k][j - 1] : MAX_LONG,
                      (i > 1 || !j) ? dp[i - 1][j] + 1ll * k * K : MAX_LONG) +
                  a[(j + k) % m];
        mi = min(f[k][j], mi);
      }
      dp[i][j] = mi;
    }
  }
  printf("%lld\n", dp[n][m - 1]);
}
int main() {
  int t = 1;
  scanf("%d", &t);
  while (t--)
    work();
  return 0;
}