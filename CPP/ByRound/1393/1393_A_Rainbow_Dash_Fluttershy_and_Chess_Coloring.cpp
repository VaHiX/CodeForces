/*
 * Problem URL : https://codeforces.com/contest/1393/problem/A
 * Submit Date : 2025-08-25
 */

#include <cstdio>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long x;
    scanf("%ld", &x);
    printf("%ld\n", 1 + x / 2);
  }

  return 0;
}
