/*
 * Problem URL : https://codeforces.com/contest/289/problem/A
 * Submit Date : 2025-09-06
 */

#include <cstdio>

int main() {
  int n, k, l, r, s(0);
  scanf("%d%d", &n, &k);
  while (n--) {
    scanf("%d%d", &l, &r);
    s = (s + r - l + 1) % k;
  }
  printf("%d\n", (k - s) % k);
  return 0;
}
