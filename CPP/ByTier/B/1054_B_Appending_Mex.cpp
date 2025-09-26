/*
 * Problem URL : https://codeforces.com/contest/1054/problem/B
 * Submit Date : 2025-09-11
 */

#include <cstdio>

int main() {

  long n;
  scanf("%ld", &n);
  long m(-1);
  for (long p = 0; p < n; p++) {
    long a;
    scanf("%ld", &a);
    if (a > m + 1) {
      printf("%ld\n", p + 1);
      return 0;
    }
    m = (m > a) ? m : a;
  }

  puts("-1");

  return 0;
}
