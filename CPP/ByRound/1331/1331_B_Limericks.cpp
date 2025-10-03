/*
 * Problem URL : https://codeforces.com/contest/1331/problem/B
 * Submit Date : 2025-09-07
 */

#include <cstdio>

int main() {

  long a;
  scanf("%ld", &a);
  long x(1), y(a);
  for (long p = 2; p * p <= a; p++) {
    if (a % p) {
      continue;
    }
    x = p;
    y = a / p;
    break;
  }

  printf("%ld%ld\n", x, y);

  return 0;
}
