/*
 * Problem URL : https://codeforces.com/problemset/problem/669/A
 * Submit Date : 2025-08-18
 */

#include <cstdio>

int main() {

  long n;
  scanf("%ld\n", &n);
  printf("%ld\n", 2 * (n / 3) + (n % 3 > 0));

  return 0;
}
