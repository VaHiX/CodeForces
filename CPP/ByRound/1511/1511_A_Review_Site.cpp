/*
 * Problem URL : https://codeforces.com/problemset/problem/1511/A
 * Submit Date : 2025-08-23
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long cnt(0);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      cnt += (x != 2);
    }

    printf("%ld\n", cnt);
  }
}
