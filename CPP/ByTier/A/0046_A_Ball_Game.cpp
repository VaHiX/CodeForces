/*
 * Problem URL : https://codeforces.com/problemset/problem/12/A
 * Submit Date : 2025-08-08
 */

#include <cstdio>

int main() {

  int n;
  scanf("%d", &n);
  int current(0);
  for (int k = 1; k < n; k++) {
    current += k;
    current %= n;
    printf("%d ", current + 1);
  }
  printf("\n");
  return 0;
}
