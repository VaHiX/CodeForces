/*
 * Problem URL : https://codeforces.com/problemset/problem/239/A
 * Submit Date : 2025-08-09
 */

#include <cstdio>

int main() {
  int y, k, n;
  scanf("%d%d%d", &y, &k, &n);
  int x = k - y % k;
  int top = n - y;
  if (x <= top) {
    printf("%d", x);
    x += k;
    while (x <= top) {
      printf(" %d", x);
      x += k;
    }
    printf("\n");
  } else {
    printf("-1\n");
  }
  return 0;
}
