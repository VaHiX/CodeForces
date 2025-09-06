/*
 * Problem URL : https://codeforces.com/problemset/problem/1684/B
 * Submit Date : 2025-08-23
 */

#include <cstdio>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long long a, b, c;
    scanf("%lld %lld %lld", &a, &b, &c);
    printf("%lld %lld %lld\n", a + b + c, b + c, c);
  }
}
