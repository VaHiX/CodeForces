/*
 * Problem URL : https://codeforces.com/contest/484/problem/A
 * Submit Date : 2025-09-06
 */

#include <stdio.h>

int n;

int main() {
  scanf("%d", &n);
  while (n--) {
    long long l, r;
    scanf("%lld%lld", &l, &r);
    long long x = 1;
    while ((l | x) <= r) {
      l = l | x;
      x = x << 1;
    }
    printf("%lld\n", l);
  }
  return 0;
}