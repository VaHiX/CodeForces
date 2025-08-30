/*
 * Problem URL : https://codeforces.com/problemset/problem/237/A
 * Submit Date : 2025-08-09
 */

#include <stdio.h>

int main() {
  int n, h, m, h0, m0, c(1), cash(1);
  scanf("%d", &n);
  scanf("%d%d", &h0, &m0);

  while (--n) {
    scanf("%d%d", &h, &m);
    if (h == h0 && m == m0) {
      c += 1;
      if (c > cash) {
        cash = c;
      }
    } else {
      c = 1;
    }
    h0 = h;
    m0 = m;
  }
  printf("%d\n", cash);
  return 0;
}
