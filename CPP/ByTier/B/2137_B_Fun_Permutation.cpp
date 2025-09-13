/*
 * Problem URL : https://codeforces.com/contest/2137/problem/B
 * Submit Date : 2025-09-07
 */

#include <cstdio>
int n, T, i, p;
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
      scanf("%d", &p);
      printf("%d ", n + 1 - p);
    }
    printf("\n");
  }
}