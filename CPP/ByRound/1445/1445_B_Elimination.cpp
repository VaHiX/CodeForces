/*
 * Problem URL : https://codeforces.com/contest/1445/problem/B
 * Submit Date : 2025-08-26
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b, c, d;
    scanf("%ld %ld %ld %ld", &a, &b, &c, &d);
    long u = a + b;
    long v = c + d;
    long ans = (u > v) ? u : v;
    printf("%ld\n", ans);
  }

  return 0;
}
