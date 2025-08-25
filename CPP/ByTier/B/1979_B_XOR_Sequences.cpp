/*
 * Problem URL : https://codeforces.com/problemset/problem/1979/B
 * Submit Date : 2025-08-12
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long x, y;
    scanf("%ld %ld", &x, &y);
    long z = x ^ y;
    long res(1);
    while (z % 2 == 0) {
      res *= 2;
      z /= 2;
    }
    printf("%ld\n", res);
  }
}
