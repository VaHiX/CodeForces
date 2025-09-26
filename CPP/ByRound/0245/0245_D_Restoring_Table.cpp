/*
 * Problem URL : https://codeforces.com/problemset/problem/245/D
 * Submit Date : 2025-08-20
 */

#include <cstdio>

int main() {

  long n;
  scanf("%ld", &n);
  for (long row = 0; row < n; row++) {
    long a(0);
    for (long col = 0; col < n; col++) {
      long m;
      scanf("%ld", &m);
      if (m < 0) {
        continue;
      }
      a |= m;
    }

    printf("%ld ", a);
  }

  puts("");

  return 0;
}
