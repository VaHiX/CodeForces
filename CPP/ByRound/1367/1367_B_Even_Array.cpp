/*
 * Problem URL : https://codeforces.com/contest/1367/problem/B
 * Submit Date : 2025-09-07
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long w(0), v(0);
    for (long p = 0; p < n; p++) {
      long a;
      scanf("%ld", &a);
      if (p % 2 < a % 2) {
        ++w;
      } else if (p % 2 > a % 2) {
        ++v;
      }
    }

    if (w == v) {
      printf("%ld\n", w);
    } else {
      puts("-1");
    }
  }

  return 0;
}
