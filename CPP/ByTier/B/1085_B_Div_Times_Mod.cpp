/*
 * Problem URL : https://codeforces.com/contest/1085/problem/B
 * Submit Date : 2025-09-11
 */

#include <cstdio>

int main() {

  long n, k;
  scanf("%ld %ld", &n, &k);
  long x(0);
  for (long b = k - 1; b > 0; b--) {
    if (n % b) {
      continue;
    }
    x = (n / b) * k + b;
    break;
  }

  printf("%ld\n", x);

  return 0;
}
