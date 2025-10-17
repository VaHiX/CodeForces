/*
 * Problem URL : https://codeforces.com/problemset/problem/1447/A
 * Submit Date : 2025-08-23
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    printf("%ld\n", n);
    for (long p = 1; p <= n; p++) {
      printf("%ld\n", p);
    }
  }

  return 0;
}
