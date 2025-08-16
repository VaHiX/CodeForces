/*
 * Problem URL : https://codeforces.com/problemset/problem/268/C
 * Submit Date : 2025-08-09
 */

#include <algorithm>
#include <cstdio>

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  int k = std::min(n, m);
  printf("%d\n", k + 1);
  for (int i = 0; i <= k; ++i) {
    printf("%d %d\n", i, k - i);
  }
  return 0;
}
