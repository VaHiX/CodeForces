/*
 * Problem URL : https://codeforces.com/problemset/problem/246/B
 * Submit Date : 2025-08-09
 */

#include <cstdio>

int main() {
  int n, a, sum(0);
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a);
    sum += a;
  }
  printf("%d\n", sum % n == 0 ? n : n - 1);
  return 0;
}
