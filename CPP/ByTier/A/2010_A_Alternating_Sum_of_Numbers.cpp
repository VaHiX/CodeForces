/*
 * Problem URL : https://codeforces.com/problemset/problem/2010/A
 * Submit Date : 2025-08-10
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long long s(0);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      s += (p % 2 ? -1 : 1) * x;
    }

    printf("%lld\n", s);
  }
}
