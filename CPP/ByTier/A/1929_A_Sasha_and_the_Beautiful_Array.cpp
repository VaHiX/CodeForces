/*
 * Problem URL : https://codeforces.com/problemset/problem/1929/A
 * Submit Date : 2025-08-12
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long mn(1e9 + 7), mx(0);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      mn = (mn < x) ? mn : x;
      mx = (mx > x) ? mx : x;
    }

    printf("%ld\n", mx - mn);
  }
}
