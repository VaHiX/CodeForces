/*
 * Problem URL : https://codeforces.com/contest/1099/problem/B
 * Submit Date : 2025-09-11
 */

#include <cmath>
#include <cstdio>

int main() {

  long n;
  scanf("%ld", &n);
  long s = sqrt(n);
  long ans(0);
  if (s * s >= n) {
    ans = 2 * s;
  } else if (s * (s + 1) >= n) {
    ans = 2 * s + 1;
  } else if ((s + 1) * (s + 1) >= n) {
    ans = 2 * s + 2;
  }
  printf("%ld\n", ans);

  return 0;
}
