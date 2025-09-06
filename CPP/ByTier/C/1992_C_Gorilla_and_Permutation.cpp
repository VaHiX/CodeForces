/*
 * Problem URL : https://codeforces.com/problemset/problem/1992/C
 * Submit Date : 2025-08-11
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m, k;
    scanf("%ld %ld %ld", &n, &m, &k);
    for (long p = n; p > m; p--) {
      printf("%ld ", p);
    }
    for (long p = 1; p <= m; p++) {
      printf("%ld ", p);
    }
    puts("");
  }
}
