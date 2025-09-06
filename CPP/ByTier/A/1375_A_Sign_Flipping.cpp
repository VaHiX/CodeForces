/*
 * Problem URL : https://codeforces.com/contest/1375/problem/A
 * Submit Date : 2025-08-26
 */


#include <cstdio>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (p % 2 && x > 0) {
        printf("%ld ", -x);
      } else if (p % 2 == 0 && x < 0) {
        printf("%ld ", -x);
      } else {
        printf("%ld ", x);
      }
    }
    puts("");
  }

  return 0;
}
