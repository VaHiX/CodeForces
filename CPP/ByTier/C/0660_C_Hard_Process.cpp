/*
 * Problem URL : https://codeforces.com/problemset/problem/660/C
 * Submit Date : 2025-08-19
 */

#include <cstdio>

int a[300001];

int main() {
  int ans = 0, n, k, pi, pj;
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]);
  for (int i = 1, j = 0, cnt = 0; i <= n; cnt -= !a[i++]) {
    while (cnt <= k && j <= n)
      cnt += !a[++j];
    if (j - i > ans)
      ans = j - i, pi = i, pj = j;
  }
  printf("%d\n", ans);
  for (int i = 1; i <= n; ++i)
    printf("%d ", a[i] || (i >= pi && i < pj));
}