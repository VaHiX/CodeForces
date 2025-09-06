/*
 * Problem URL : https://codeforces.com/problemset/problem/2041/B
 * Submit Date : 2025-08-10
 */

#include <cmath>
#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long long w, b;
    scanf("%lld %lld", &w, &b);
    long double t = w + b;
    long res = (sqrt(1 + 8 * t) - 1) / 2.0;
    printf("%ld\n", res);
  }
}
