/*
 * Problem URL : https://codeforces.com/contest/1547/problem/D
 * Submit Date : 2025-09-04
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);

    long prev;
    scanf("%ld", &prev);
    printf("0 ");
    for (long p = 1; p < n; p++) {
      long x;
      scanf("%ld", &x);
      long y = prev & (~x);
      prev = x ^ y;
      printf("%ld ", y);
    }
    puts("");
  }
}
