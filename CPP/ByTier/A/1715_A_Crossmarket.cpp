/*
 * Problem URL : https://codeforces.com/problemset/problem/1715/A
 * Submit Date : 2025-08-21
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    long mn = (m > n) ? m : n;
    long ans = (m + n > 2) ? (2 * (m + n - 1) - mn) : 0;
    printf("%ld\n", ans);
  }
}
