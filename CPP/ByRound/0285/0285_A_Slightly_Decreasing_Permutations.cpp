/*
 * Problem URL : https://codeforces.com/contest/285/problem/A
 * Submit Date : 2025-09-06
 */

#include <cstdio>

int main() {
  int n, k;
  scanf("%d %d", &n, &k);
  int *perm = new int[n + 1];
  for (int u = 1; u < n - k; u++) {
    printf("%d ", u);
  }
  for (int u = n - k; u <= n; u++) {
    printf("%d ", 2 * n - k - u);
  }
  return 0;
}
