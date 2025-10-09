/*
 * Problem URL : https://codeforces.com/problemset/problem/1656/A
 * Submit Date : 2025-08-23
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long mn(1e9 + 7), mx(-1e9 - 7), idxmn(0), idxmx(0);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x > mx) {
        mx = x;
        idxmx = p + 1;
      }
      if (x < mn) {
        mn = x;
        idxmn = p + 1;
      }
    }

    printf("%ld %ld\n", idxmn, idxmx);
  }
}
