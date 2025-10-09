/*
 * Problem URL : https://codeforces.com/contest/379/problem/A
 * Submit Date : 2025-09-05
 */

#include <cstdio>

int main() {

  int a(0), b(0);
  scanf("%d %d", &a, &b);

  int total(0), full(a), partial(0);
  while (full > 0) {
    total += full;
    partial += full;
    full = partial / b;
    partial %= b;
  }

  printf("%d\n", total);
  return 0;
}
