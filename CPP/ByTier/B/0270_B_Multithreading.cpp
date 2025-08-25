/*
 * Problem URL : https://codeforces.com/problemset/problem/270/B
 * Submit Date : 2025-08-09
 */

#include <cstdio>

int main() {
  int n, a0, a, ascending(1);
  scanf("%d%d", &n, &a0);
  for (int i = 1; i < n; ++i) {
    scanf("%d", &a);
    if (a > a0) {
      ascending += 1;
    } else {
      ascending = 1;
    }
    a0 = a;
  }
  printf("%d\n", n - ascending);
  return 0;
}
