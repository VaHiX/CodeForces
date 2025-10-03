/*
 * Problem URL : https://codeforces.com/problemset/problem/1173/B
 * Submit Date : 2025-08-19
 */

#include <cstdio>

int main() {

  long n;
  scanf("%ld", &n);
  long m = n / 2 + 1;
  printf("%ld\n", m);
  for (long p = 1; p <= m; p++)
    printf("%ld 1\n", p);
  for (long p = 2; p <= n - m + 1; ++p)
    printf("%ld %ld\n", m, p);

  return 0;
}
