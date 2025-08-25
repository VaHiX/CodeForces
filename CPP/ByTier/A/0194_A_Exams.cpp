/*
 * Problem URL : https://codeforces.com/problemset/problem/12/A
 * Submit Date : 2025-08-08
 */

#include <cstdio>

int main() {
  int n, k;
  scanf("%d %d", &n, &k);
  printf("%d\n", (k > 3 * n) ? 0 : 3 * n - k);
  return 0;
}
