/*
 * Problem URL : https://codeforces.com/problemset/problem/1559/A
 * Submit Date : 2025-08-23
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long res;
    scanf("%ld", &res);
    for (long p = 1; p < n; p++) {
      long x;
      scanf("%ld", &x);
      res &= x;
    }

    printf("%ld\n", res);
  }
}
