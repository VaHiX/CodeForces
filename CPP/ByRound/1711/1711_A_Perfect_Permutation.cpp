/*
 * Problem URL : https://codeforces.com/problemset/problem/1711/A
 * Submit Date : 2025-08-21
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    for (long p = 0; p < n; p++) {
      printf("%ld ", 1 + ((p + 1) % n));
    }
    puts("");
  }
}
