/*
 * Problem URL : https://codeforces.com/contest/1632/problem/B
 * Submit Date : 2025-08-28
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long k(0);
    while ((1 << (k + 1)) <= n - 1) {
      ++k;
    }
    for (long p = (1 << k) - 1; p >= 0; p--) {
      printf("%ld ", p);
    }
    for (long p = (1 << k); p < n; p++) {
      printf("%ld ", p);
    }
    puts("");
  }
}
