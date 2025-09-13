/*
 * Problem URL : https://codeforces.com/contest/333/problem/A
 * Submit Date : 2025-09-06
 */

#include <cstdio>

int main() {

  long long n(0);
  scanf("%lld", &n);
  while (n % 3 == 0) {
    n /= 3;
  }
  printf("%lld\n", (n + 2) / 3);

  return 0;
}
