/*
 * Problem URL : https://codeforces.com/contest/588/problem/B
 * Submit Date : 2025-09-13
 */

#include <cmath>
#include <cstdio>
#include <vector>

int main() {

  long long n;
  scanf("%lld\n", &n);
  for (long long p = 2; p * p <= n; p++) {
    while (n % (p * p) == 0) {
      n /= p;
    }
  }
  printf("%lld\n", n);

  return 0;
}
