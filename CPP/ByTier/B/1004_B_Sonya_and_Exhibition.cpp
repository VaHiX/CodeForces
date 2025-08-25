/*
 * Problem URL : https://codeforces.com/problemset/problem/1004/B
 * Submit Date : 2025-08-14
 */

#include <cstdio>

int main() {

  long n;
  scanf("%ld", &n);
  for (long p = 0; p < n; p++) {
    putchar(p & 1 ? '1' : '0');
  }
  puts("");

  return 0;
}
