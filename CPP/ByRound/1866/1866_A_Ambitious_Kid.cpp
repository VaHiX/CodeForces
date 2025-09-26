/*
 * Problem URL : https://codeforces.com/problemset/problem/1866/A
 * Submit Date : 2025-08-15
 */

#include <cstdio>

int main() {

  long n;
  scanf("%ld", &n);
  long ans(1e5 + 7);
  for (long p = 0; p < n; p++) {
    long x;
    scanf("%ld", &x);
    x = (x < 0) ? -x : x;
    ans = (ans < x) ? ans : x;
  }

  printf("%ld\n", ans);
}
