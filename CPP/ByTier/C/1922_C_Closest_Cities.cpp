/*
 * Problem URL : https://codeforces.com/problemset/problem/1922/C
 * Submit Date : 2025-08-13
 */

#include <cstdio>
int T, n, a[100005], m, qz[100005], hz[100005];
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n), qz[1] = hz[n] = 0;
    for (int i = 1; i <= n; ++i)
      scanf("%d", &a[i]);
    for (int i = 1; i < n; ++i)
      qz[i + 1] =
          (i == 1 || a[i] - a[i - 1] > a[i + 1] - a[i] ? 1 : a[i + 1] - a[i]) +
          qz[i];
    for (int i = n; i > 1; --i)
      hz[i - 1] =
          (i == n || a[i] - a[i - 1] < a[i + 1] - a[i] ? 1 : a[i] - a[i - 1]) +
          hz[i];
    scanf("%d", &m);
    int x, y;
    while (m--) {
      scanf("%d%d", &x, &y);
      if (y > x)
        printf("%d\n", qz[y] - qz[x]);
      else
        printf("%d\n", hz[y] - hz[x]);
    }
  }
  return 0;
}