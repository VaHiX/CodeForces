/*
 * Problem URL : https://codeforces.com/contest/506/problem/A
 * Submit Date : 2025-09-06
 */

#include <bits/stdc++.h>
using namespace std;
const int N = 30000;

int n, d, a[N + 5], p;
int f[N + 5][505], ans;

void work() {
  scanf("%d%d", &n, &d);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &p);
    a[p]++;
  }
  memset(f, -1, sizeof(f));
  f[d][250] = a[d];
  for (int i = d; i <= N; i++)
    for (int j = 1; j <= 500; j++)
      if (f[i][j] != -1) {
        ans = max(ans, f[i][j]);
        int l = d + j - 250;
        if (l > 1 && i + l - 1 <= N)
          f[i + l - 1][j - 1] =
              max(f[i + l - 1][j - 1], f[i][j] + a[i + l - 1]);
        if (i + l <= N)
          f[i + l][j] = max(f[i + l][j], f[i][j] + a[i + l]);
        if (i + l + 1 <= N)
          f[i + l + 1][j + 1] =
              max(f[i + l + 1][j + 1], f[i][j] + a[i + l + 1]);
      }
  printf("%d\n", ans);
}
int main() {
  work();
  return 0;
}
