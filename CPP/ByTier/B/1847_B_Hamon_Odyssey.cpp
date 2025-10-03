/*
 * Problem URL : https://codeforces.com/problemset/problem/1847/B
 * Submit Date : 2025-08-18
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long cur;
    scanf("%ld", &cur);
    long cnt(0);

    for (long p = 1; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (!cur) {
        ++cnt;
        cur = x;
      } else {
        cur &= x;
      }
    }

    cnt += (!cur);
    cnt += (!cnt);
    printf("%ld\n", cnt);
  }
}
