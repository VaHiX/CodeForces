/*
 * Problem URL : https://codeforces.com/problemset/problem/478/B
 * Submit Date : 2025-08-18
 */

#include <cstdio>

int main() {

  long long n, m;
  scanf("%lld %lld\n", &n, &m);
  long long minPairs = ((n % m) * (n / m + 1) * (n / m) / 2) +
                       ((m - n % m) * (n / m) * (-1 + n / m) / 2);
  long long maxPairs = (n - m + 1) * (n - m) / 2;
  printf("%lld %lld\n", minPairs, maxPairs);

  return 0;
}
