/*
 * Problem URL : https://codeforces.com/problemset/problem/1604/A
 * Submit Date : 2025-08-23
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long res(0);
    for (long p = 1; p <= n; p++) {
      long x;
      scanf("%ld", &x);
      long diff = x - p;
      res = (res > diff) ? res : diff;
    }

    printf("%ld\n", res);
  }
}
