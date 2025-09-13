/*
 * Problem URL : https://codeforces.com/problemset/problem/1736/C1
 * Submit Date : 2025-08-21
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long s(0);
    long long cnt(0);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      ++s;
      s = (s < x ? s : x);
      cnt += s;
    }

    printf("%lld\n", cnt);
  }
}
