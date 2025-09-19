/*
 * Problem URL : https://codeforces.com/problemset/problem/201/A
 * Submit Date : 2025-08-21
 */

#include <cstdio>

int main() {

  int x;
  scanf("%d", &x);
  long n(1);
  while ((n * n + 1) / 2 < x) {
    n += 2;
  }

  printf("%ld", (x == 3) ? 5 : n);
  return 0;
}
