/*
 * Problem URL : https://codeforces.com/problemset/problem/282/B
 * Submit Date : 2025-08-08
 */

#include <cstdio>

int main() {
  int n, a, g;
  scanf("%d", &n);

  int A(0);
  while (n--) {
    scanf("%d%d", &a, &g);
    A += a;
    if (A <= 500) {
      printf("A");
    } else {
      A -= 1000;
      printf("G");
    }
  }
  printf("\n");

  return 0;
}
