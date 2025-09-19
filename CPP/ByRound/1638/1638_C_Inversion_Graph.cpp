/*
 * Problem URL : https://codeforces.com/contest/1638/problem/C
 * Submit Date : 2025-09-07
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long mx(0), cnt(0);
    for (long p = 1; p <= n; p++) {
      long x;
      scanf("%ld", &x);
      mx = (mx > x) ? mx : x;
      cnt += (mx == p);
    }

    printf("%ld\n", cnt);
  }
}
