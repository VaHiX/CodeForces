/*
 * Problem URL : https://codeforces.com/problemset/problem/1136/B
 * Submit Date : 2025-08-13
 */

#include <cstdio>

int main() {

  long n, k;
  scanf("%ld %ld", &n, &k);
  long x = (2 * k <= n + 1) ? (k - 1) : (n - k);
  long ans = 3 * n + x;
  printf("%ld\n", ans);

  return 0;
}
