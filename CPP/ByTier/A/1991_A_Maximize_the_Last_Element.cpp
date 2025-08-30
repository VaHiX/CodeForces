/*
 * Problem URL : https://codeforces.com/problemset/problem/1991/A
 * Submit Date : 2025-08-11
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long mx(-1);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (p % 2) {
        continue;
      }
      mx = (mx > x ? mx : x);
    }

    printf("%ld\n", mx);
  }
}
