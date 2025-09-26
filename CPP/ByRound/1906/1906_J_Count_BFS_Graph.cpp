/*
 * Problem URL : https://codeforces.com/contest/1906/problem/J
 * Submit Date : 2025-09-07
 */

#include <bits/stdc++.h>
using namespace std;
const int N = 5010, mod = 998244353;
int f[N][N], a[N], P[N];
int main() {
  int n;
  scanf("%d", &n);
  P[0] = 1;
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    P[i] = 2 * P[i - 1] % mod;
  }
  f[2][1] = f[2][2] = 1;
  for (int i = 3; i <= n; i++) {
    for (int j = 1; j < i; j++) {
      if (a[i] > a[i - 1])
        f[i][j] = 1ll * P[i - j - 1] * f[i - 1][j] % mod;
      else
        f[i][j] = 1ll * P[i - j - 1] * f[i - 1][j - 1] % mod;
    }
    for (int j = 1; j <= i; j++)
      f[i][j] = (f[i][j] + f[i][j - 1]) % mod;
  }
  printf("%d\n", f[n][n]);
  return 0;
}
