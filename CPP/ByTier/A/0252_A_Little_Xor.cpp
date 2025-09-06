/*
 * Problem URL : https://codeforces.com/problemset/problem/252/A
 * Submit Date : 2025-08-09
 */

#include <cstdio>

int main() {
  int n, a, x[101] = {0};
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a);
    x[i] = x[i - 1] ^ a;
  }
  int maximal = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j <= n; ++j) {
      int xx = x[i] ^ x[j];
      if (xx > maximal) {
        maximal = xx;
      }
    }
  }
  printf("%d\n", maximal);
  return 0;
}
