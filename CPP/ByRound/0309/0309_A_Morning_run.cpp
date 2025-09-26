/*
 * Problem URL : https://codeforces.com/problemset/problem/309/A
 * Submit Date : 2025-08-13
 */

#include <stdio.h>
int n, l, t, a[2000005];
int main() {
  scanf("%d%d%d", &n, &l, &t);
  for (int i = 0; i < n; ++i) {
    scanf("%d", a + i);
    a[i + n] = a[i] + l;
  }
  int k = 2 * t / l, p = 2 * t % l;
  double ans = 1.0 * k * n * (n - 1);
  for (int i = 0, cnt = 0; i < n; i++) {
    while (cnt < n + i && a[cnt] - a[i] <= p)
      cnt++;
    ans += cnt - i - 1;
  }
  printf("%.20f\n", ans / 4);
  return 0;
}