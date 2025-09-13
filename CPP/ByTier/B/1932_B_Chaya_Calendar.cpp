/*
 * Problem URL : https://codeforces.com/problemset/problem/1932/B
 * Submit Date : 2025-08-12
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long ans(0);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      ans = ((ans / x) + 1) * x;
    }

    printf("%ld\n", ans);
  }
}
