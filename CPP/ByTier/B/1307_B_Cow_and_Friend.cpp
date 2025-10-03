/*
 * Problem URL : https://codeforces.com/contest/1307/problem/B
 * Submit Date : 2025-08-30
 */

#include <stdio.h>
int n, x, maxx, f, t;
int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d%d", &n, &x);
    f = 0;
    maxx = 1;
    for (int i = 1; i <= n; i++) {
      int p;
      scanf("%d", &p);
      if (p == x)
        f = 1;
      if (p > maxx)
        maxx = p;
    }
    printf("%d\n", f ? 1 : (maxx < x ? (x - 1) / maxx + 1 : 2));
  }
}