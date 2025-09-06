/*
 * Problem URL : https://codeforces.com/problemset/problem/1981/A
 * Submit Date : 2025-08-12
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long l, r;
    scanf("%ld %ld", &l, &r);
    long cnt(0);
    long x(1);
    for (long p = 1; 2 * p <= r; p *= 2, ++cnt)
      ;
    printf("%ld\n", cnt);
  }
}
