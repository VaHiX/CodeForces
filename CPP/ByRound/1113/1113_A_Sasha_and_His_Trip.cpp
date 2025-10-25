/*
 * Problem URL : https://codeforces.com/contest/1113/problem/A
 * Submit Date : 2025-08-28
 */

#include <cstdio>

int main() {

  long n, v;
  scanf("%ld %ld", &n, &v);
  long ans = (v - 1) + (n - v) * (n - v + 1) / 2;
  if (v >= n) {
    ans = n - 1;
  }
  printf("%ld\n", ans);

  return 0;
}
