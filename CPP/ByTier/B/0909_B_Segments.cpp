/*
 * Problem URL : https://codeforces.com/contest/909/problem/B
 * Submit Date : 2025-09-07
 */

#include <cstdio>

int main() {

  long n;
  scanf("%ld", &n);
  if (n % 2) {
    printf("%ld\n", (n + 1) * (n + 1) / 4);
  } else {
    printf("%ld\n", (n / 2) * (n / 2 + 1));
  }

  return 0;
}
