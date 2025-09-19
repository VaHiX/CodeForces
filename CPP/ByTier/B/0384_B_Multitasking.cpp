/*
 * Problem URL : https://codeforces.com/contest/384/problem/B
 * Submit Date : 2025-09-08
 */

#include <cstdio>

int main() {

  long n(0), m(0), k(0);
  scanf("%ld %ld %ld", &n, &m, &k);
  printf("%ld\n", m * (m - 1) / 2);
  for (long p = 1; p < m; p++) {
    for (long q = p + 1; q <= m; q++) {
      if (!k) {
        printf("%ld %ld\n", p, q);
      } else {
        printf("%ld %d\n", q, p);
      }
    }
  }

  return 0;
}
