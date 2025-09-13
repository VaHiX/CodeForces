/*
 * Problem URL : https://codeforces.com/contest/471/problem/C
 * Submit Date : 2025-09-05
 */

#include <cmath>
#include <cstdio>

int main() {

  long long n;
  scanf("%lld\n", &n);
  long long maxFloors = (-1 + sqrt(1 + 24 * n)) / 6.0;
  maxFloors -= (n + maxFloors) % 3;
  printf("%lld\n", (maxFloors + 2) / 3);

  return 0;
}
