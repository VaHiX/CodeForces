/*
 * Problem URL : https://codeforces.com/contest/1214/problem/B
 * Submit Date : 2025-09-11
 */

#include <cstdio>

int main() {

  long b, g, n;
  scanf("%ld %ld %ld", &b, &g, &n);
  long mnb(0), mxb(b);
  if (g < n) {
    mnb = n - g;
  }
  if (n < b) {
    mxb = n;
  }
  printf("%ld\n", mxb - mnb + 1);

  return 0;
}
