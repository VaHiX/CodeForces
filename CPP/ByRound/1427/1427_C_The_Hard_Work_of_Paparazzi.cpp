/*
 * Problem URL : https://codeforces.com/problemset/problem/1427/C
 * Submit Date : 2025-08-14
 */

#include <bits/stdc++.h>
using namespace std;
int r, n, x[100010], y[100010], t[100010], f[100010], maxn[100010], ans = 0;
int main() {
  scanf("%d%d", &r, &n);
  for (int i = 1; i <= n; i++)
    scanf("%d%d%d", &t[i], &x[i], &y[i]), f[i] = -1;
  x[0] = y[0] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = i - 1; j >= 0; j--) {
      if (f[j] >= 0 && abs(x[i] - x[j]) + abs(y[i] - y[j]) <= t[i] - t[j])
        f[i] = max(f[i], f[j] + 1);
      if (f[i] >= maxn[j] + 1)
        break;
    }
    ans = max(ans, f[i]);
    maxn[i] = max(maxn[i - 1], f[i]);
  }
  printf("%d\n", ans);
}