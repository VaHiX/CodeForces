/*
 * Problem URL : https://codeforces.com/problemset/problem/1840/C
 * Submit Date : 2025-08-18
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k, q;
    scanf("%ld %ld %ld", &n, &k, &q);
    long long cnt(0), res(0);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x <= q) {
        ++cnt;
      } else {
        cnt = 0;
      }
      res += (cnt >= k) ? (cnt - k + 1) : 0;
    }

    printf("%lld\n", res);
  }
}
