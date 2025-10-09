/*
 * Problem URL : https://codeforces.com/problemset/problem/315/B
 * Submit Date : 2025-08-09
 */

#include <cstdio>

int main() {
  int n, m, a[100001], t, v, x, y, q, increase(0);
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }

  while (m--) {
    scanf("%d", &t);
    switch (t) {
    case 1:
      scanf("%d%d", &v, &x);
      a[v] = x - increase;
      break;

    case 2:
      scanf("%d", &y);
      increase += y;
      break;

    case 3:
      scanf("%d", &q);
      printf("%d\n", a[q] + increase);
      break;

    default:
      break;
    }
  }
}
