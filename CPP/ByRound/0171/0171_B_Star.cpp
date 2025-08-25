/*
 * Problem URL : https://codeforces.com/problemset/problem/12/A
 * Submit Date : 2025-08-08
 */

#include <cstdio>

int main() {

  long long n(0);
  scanf("%lld", &n);
  printf("%lld\n", 6 * n * (n - 1) + 1);

  return 0;
}
