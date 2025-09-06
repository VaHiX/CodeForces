/*
 * Problem URL : https://codeforces.com/problemset/problem/1790/B
 * Submit Date : 2025-08-20
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, s, r;
    scanf("%ld %ld %ld", &n, &s, &r);
    long u = s - r;
    printf("%ld ", u);
    for (long p = n - 1; p >= 1; p--) {
      long a = r - p + 1;
      a = (a < u ? a : u);
      printf("%ld ", a);
      r -= a;
    }
    puts("");
  }
}
