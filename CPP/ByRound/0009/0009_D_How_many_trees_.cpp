/*
 * Problem URL : https://codeforces.com/contest/9/problem/D
 * Submit Date : 2025-08-25
 */

#include <cstdio>
int n, h;
long long f[45][45];
int main() {
  scanf("%d%d", &n, &h);
  for (int i = 1; i <= n; i++) {
    f[0][i - 1] = 1;
    for (int j = 1; j <= n; j++)
      for (int k = 0; k < j; k++)
        f[j][i] += f[k][i - 1] * f[j - k - 1][i - 1];
  }
  printf("%lld\n", f[n][n] - f[n][h - 1]);
}