/*
 * Problem URL : https://codeforces.com/problemset/problem/1838/A
 * Submit Date : 2025-08-18
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long neg(0), mx(0);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x < 0) {
        neg = x;
      }
      mx = (mx > x) ? mx : x;
    }

    printf("%ld\n", (neg < 0) ? neg : mx);
  }
}
