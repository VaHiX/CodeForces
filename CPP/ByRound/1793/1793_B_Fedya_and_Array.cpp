/*
 * Problem URL : https://codeforces.com/problemset/problem/1793/B
 * Submit Date : 2025-08-20
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long x, y;
    scanf("%ld %ld", &x, &y);
    printf("%ld\n", 2 * (x - y));
    for (long p = y; p <= x; p++) {
      printf("%ld ", p);
    }
    for (long p = x - 1; p > y; p--) {
      printf("%ld ", p);
    }
    puts("");
  }
}
